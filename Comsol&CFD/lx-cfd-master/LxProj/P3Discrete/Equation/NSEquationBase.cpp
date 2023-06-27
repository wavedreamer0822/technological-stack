#include "NSEquationBase.h"

namespace LxCFD
{
    double NSEquationBase::MUSCL_DC::cal(double r, double gCf)
    {
        return std::max<double>(0, std::min<double>(std::min(2 * gCf * r, (r + 1) * gCf / 2), 1));
        // return Math.Max(0, Math.Min(Math.Min(4 * gCf * r, (r + 1) * gCf), 2));
    }
    double NSEquationBase::OSHER_DC::cal(double r, double gCf)
    {
        return std::max<double>(0, std::min<double>(gCf * r, 1));
    }
    void NSEquationBase::set_x_flow(Value1Base<double> &baseValue, IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        int ncell = 0;
        if (i1 < endp1)
            ncell = Faces->at(i1).NSideCell;
        for (; i1 < endp1; i1++, ncell++)
        {
            if (MassFlux->at(i1) > 0) //由明确的流出时，确定为流出边界
            {
                CalBoundValue_grad0(Faces->at(i1));
            }
            else
            {
                x->at(ncell) = baseValue.GetCellValue(ncell);
            }
        }
    }

    double NSEquationBase::calUpwindValue_faceFluxPositive(FvFace &face, double phiO, double phiN, double velDirCor)
    {
        double upwindvalue = phiN - 2 * Vector3d::DotProduct(Grad->at(face.OSideCell), face.OToN);
        return upwindvalue * velDirCor + phiO * (1 - velDirCor);
    }

    double NSEquationBase::calUpwindValue_faceFluxNegative(FvFace &face, double phiO, double phiN, double velDirCor)
    {
        double upwindvalue = phiO + 2 * Vector3d::DotProduct(Grad->at(face.NSideCell), face.OToN);
        return upwindvalue * velDirCor + phiN * (1 - velDirCor);
    }

    void NSEquationBase::set_Ab_Upwind_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            double taugdiff = gamma * face.gDiff;
            double massflux = MassFlux->at(i1) * Conv->GetFaceValue(i1);
            b_FaceCommon->at(i1) = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
            if (massflux >= 0)
            {
                ALUO->at(i1) = -taugdiff;
                ALUN->at(i1) = -(massflux + taugdiff);
            }
            else
            {
                ALUO->at(i1) = massflux - taugdiff;
                ALUN->at(i1) = -taugdiff;
            }
        }
    }

    void NSEquationBase::set_Ab_SOU_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            double conv = Conv->GetFaceValue(i1);
            double gamadiff = gamma * face.gDiff;
            double massflux = MassFlux->at(i1) * conv;
            double facecor = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
            double veldircor = std::exp(-VelocityDirectionCorrection->at(i1) * conv / gamma);
            if (massflux >= 0)
            {
                double phiOO = calUpwindValue_faceFluxPositive(face, x->at(face.OSideCell), x->at(face.NSideCell), veldircor);
                double massgo = massflux * face.gOwner;
                b_FaceCommon->at(i1) = massgo * phiOO + facecor;
                ALUO->at(i1) = -gamadiff;
                ALUN->at(i1) = -(massflux + massgo + gamadiff);
            }
            else
            {
                double phiNN = calUpwindValue_faceFluxNegative(face, x->at(face.OSideCell), x->at(face.NSideCell), veldircor);
                double massgn = massflux * (1 - face.gOwner);
                b_FaceCommon->at(i1) = massgn * phiNN + facecor;
                ALUO->at(i1) = massflux + massgn - gamadiff;
                ALUN->at(i1) = -gamadiff;
            }
        }
    }

    void NSEquationBase::set_Ab_OSHER_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            double conv = Conv->GetFaceValue(i1);
            double gamadiff = gamma * face.gDiff;
            double massflux = MassFlux->at(i1) * conv;
            double phiO = x->at(face.OSideCell);
            double phiN = x->at(face.NSideCell);
            double facecor = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
            double veldircor = std::exp(-VelocityDirectionCorrection->at(i1) * conv / gamma);
            if (massflux >= 0)
            {
                double phiOO = calUpwindValue_faceFluxPositive(face, phiO, phiN, veldircor);
                double N_O = phiN - phiO;
                if (N_O != 0)
                {
                    double r = (phiO - phiOO) / N_O;
                    if (r < 0)
                    {
                    }
                    else if (face.gOwner * r < 1)
                    {
                        double massgo = massflux * face.gOwner;
                        b_FaceCommon->at(i1) = massgo * phiOO + facecor;
                        ALUO->at(i1) = -gamadiff;
                        ALUN->at(i1) = -(massflux + massgo + gamadiff);
                        continue;
                    }
                    else
                    {
                        b_FaceCommon->at(i1) = -massflux * N_O + facecor;
                        ALUO->at(i1) = -gamadiff;
                        ALUN->at(i1) = -(massflux + gamadiff);
                        continue;
                    }
                }
                b_FaceCommon->at(i1) = facecor;
                ALUO->at(i1) = -gamadiff;
                ALUN->at(i1) = -(massflux + gamadiff);
                continue;
            }
            else
            {
                double phiNN = calUpwindValue_faceFluxNegative(face, phiO, phiN, veldircor);
                double O_N = phiO - phiN;
                if (O_N != 0)
                {
                    double gc = 1 - face.gOwner;
                    double r = (phiN - phiNN) / O_N;
                    if (r < 0)
                    {
                    }
                    else if (gc * r < 1)
                    {
                        double massgn = massflux * gc;
                        b_FaceCommon->at(i1) = massgn * phiNN + facecor;
                        ALUO->at(i1) = massflux + massgn - gamadiff;
                        ALUN->at(i1) = -gamadiff;
                        continue;
                    }
                    else
                    {
                        b_FaceCommon->at(i1) = -massflux * O_N + facecor;
                        ALUO->at(i1) = massflux - gamadiff;
                        ALUN->at(i1) = -gamadiff;
                        continue;
                    }
                }
                b_FaceCommon->at(i1) = facecor;
                ALUO->at(i1) = massflux - gamadiff;
                ALUN->at(i1) = -gamadiff;
                continue;
            }
        }
    }

    void NSEquationBase::set_Ab_MUSCL_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            double conv = Conv->GetFaceValue(i1);
            double taugdiff = gamma * face.gDiff;
            double massflux = MassFlux->at(i1) * conv;
            double phiO = x->at(face.OSideCell);
            double phiN = x->at(face.NSideCell);
            double facecor = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
            double veldircor = std::exp(-VelocityDirectionCorrection->at(i1) * conv / gamma);
            if (massflux >= 0)
            {
                double phiOO = calUpwindValue_faceFluxPositive(face, phiO, phiN, veldircor);
                double N_O = phiN - phiO;
                if (N_O != 0)
                {
                    double r = (phiO - phiOO) / N_O;
                    if (r < LxTool::OneThird)
                    {
                        if (r < 0)
                        {
                        }
                        else
                        {
                            double mass2go = massflux * 2 * face.gOwner;
                            b_FaceCommon->at(i1) = mass2go * phiOO + facecor;
                            ALUO->at(i1) = -taugdiff;
                            ALUN->at(i1) = -(massflux + mass2go + taugdiff);
                            continue;
                        }
                    }
                    else
                    {
                        if (r * face.gOwner < 2 - face.gOwner)
                        {
                            double mass05go = massflux * 0.5 * face.gOwner;
                            b_FaceCommon->at(i1) = mass05go * phiOO + facecor;
                            ALUO->at(i1) = mass05go - taugdiff;
                            ALUN->at(i1) = -(massflux + taugdiff);
                            continue;
                        }
                        else
                        {
                            b_FaceCommon->at(i1) = -massflux * N_O + facecor;
                            ALUO->at(i1) = -taugdiff;
                            ALUN->at(i1) = -(massflux + taugdiff);
                            continue;
                        }
                    }
                }
                b_FaceCommon->at(i1) = facecor;
                ALUO->at(i1) = -taugdiff;
                ALUN->at(i1) = -(massflux + taugdiff);
                continue;
            }
            else
            {
                double phiNN = calUpwindValue_faceFluxNegative(face, phiO, phiN, veldircor);
                double O_N = phiO - phiN;
                if (O_N != 0)
                {
                    double gc = 1 - face.gOwner;
                    double r = (phiN - phiNN) / O_N;
                    if (r < LxTool::OneThird)
                    {
                        if (r < 0)
                        {
                        }
                        else
                        {
                            double mass2gn = massflux * 2 * gc;
                            b_FaceCommon->at(i1) = mass2gn * phiNN + facecor;
                            ALUO->at(i1) = massflux + mass2gn - taugdiff;
                            ALUN->at(i1) = -taugdiff;
                            continue;
                        }
                    }
                    else
                    {
                        if (r * gc < 2 - gc)
                        {
                            double mass05gn = massflux * 0.5 * gc;
                            b_FaceCommon->at(i1) = mass05gn * phiNN + facecor;
                            ALUO->at(i1) = massflux - taugdiff;
                            ALUN->at(i1) = -(mass05gn + taugdiff);
                            continue;
                        }
                        else
                        {
                            b_FaceCommon->at(i1) = -massflux * O_N + facecor;
                            ALUO->at(i1) = massflux - taugdiff;
                            ALUN->at(i1) = -taugdiff;
                            continue;
                        }
                    }
                }
                b_FaceCommon->at(i1) = facecor;
                ALUO->at(i1) = massflux - taugdiff;
                ALUN->at(i1) = -taugdiff;
                continue;
            }
        }
    }

    void NSEquationBase::set_Ab_TVD_DC_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            double conv = Conv->GetFaceValue(i1);
            double taugdiff = gamma * face.gDiff;
            double massflux = MassFlux->at(i1) * conv;
            double phiO = x->at(face.OSideCell);
            double phiN = x->at(face.NSideCell);
            double facecor = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
            double veldircor = std::exp(-VelocityDirectionCorrection->at(i1) * conv / gamma);
            if (massflux >= 0)
            {
                double N_O = phiN - phiO;
                double r = 1;
                if (N_O != 0)
                {
                    r = 2 * Vector3d::DotProduct(Grad->at(face.OSideCell), face.OToN) / N_O - 1;
                    r *= veldircor;
                    r = CalgCfPhir->cal(r, face.gOwner);
                }
                b_FaceCommon->at(i1) = -massflux * r * N_O + facecor;
                ALUO->at(i1) = -taugdiff;
                ALUN->at(i1) = -(massflux + taugdiff);
            }
            else
            {
                double O_N = phiO - phiN;
                double r = 1;
                if (O_N != 0)
                {
                    r = -2 * Vector3d::DotProduct(Grad->at(face.NSideCell), face.OToN) / O_N - 1;
                    r *= veldircor;
                    r = CalgCfPhir->cal(r, 1 - face.gOwner);
                }
                b_FaceCommon->at(i1) = -massflux * r * O_N + facecor;
                ALUO->at(i1) = massflux - taugdiff;
                ALUN->at(i1) = -taugdiff;
            }
        }
    }

    void NSEquationBase::set_Ab_boundOwner_DiffPart(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            ALUO->at(i1) = ALUN->at(i1) = -gamma * face.gDiff; //A_LU_N赋值是为了给face.ownercell用的，用来计算A_Diag
            b_FaceCommon->at(i1) = gamma * face.CalNonOrthogonalityCorrection_bound(*Grad, *x);
        }
    }

    void NSEquationBase::set_A_boundOwner_0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            ALUO->at(i1) = ALUN->at(i1) = 0; //A_LU_N赋值是为了给face.ownercell用的，用来计算A_Diag
            b_FaceCommon->at(i1) = 0;        //如果数组共用，可能有错误，需赋值
        }
    }

    void NSEquationBase::set_Ab_bound_flow(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            double massflux = MassFlux->at(i1) * Conv->GetFaceValue(i1);
            if (massflux > 0) //由明确的流出时，确定为流出边界
            {
                //向外流出，边界条件为：梯度为0，因此A_LU_O设置为0
                ALUO->at(i1) = 0;
                ALUN->at(i1) = -massflux;
                b_FaceCommon->at(i1) = massflux * (x->at(face.OSideCell) - x->at(face.NSideCell)); //用downwind格式
                                                                                                   //对于N，不计算，通过updatebound算出
            }
            else
            {
                //流入，边界条件为：固定值，A_LU_O选择计算（如果仍然假设梯度为0会怎样？）
                double gamma = Gamma->GetFaceValue(i1);
                double taugdiff = gamma * face.gDiff;
                b_FaceCommon->at(i1) = gamma * face.CalNonOrthogonalityCorrection_bound(*Grad, *x);
                ALUO->at(i1) = massflux - taugdiff;
                ALUN->at(i1) = -taugdiff;
                //对于N，不计算，通过updatebound算出
            }
        }
    }

    void NSEquationBase::setAb_step2(Value1Base<double> *source1, int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        if (source1->IsEqual0())
        {
            for (; i1 < endp1; i1++)
            {
                FvCell &cell = Cells->at(i1);
                double massimb = MassImbalance->at(i1) * Conv->GetCellValue(i1);
                ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO) - massimb; //有个规律，ADiag恰好是O面加上ALUN，N面加上ALUO
                b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon);
            }
        }
        else
        {
            for (; i1 < endp1; i1++)
            {
                FvCell &cell = Cells->at(i1);
                double massimb = MassImbalance->at(i1) * Conv->GetCellValue(i1);
                ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO) - massimb; //有个规律，ADiag恰好是O面加上ALUN，N面加上ALUO
                b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon) + source1->GetCellValue(i1) * cell.Volumn;
            }
        }
    }

    void NSEquationBase::setAb_step2(Value2Base<double> *source2, int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvCell &cell = Cells->at(i1);
            double massimb = MassImbalance->at(i1) * Conv->GetCellValue(i1);
            double S_Ad, S_b;
            source2->GetCellValue(S_Ad, S_b, i1);
            ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO) - massimb - S_Ad * cell.Volumn;
            b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon) + S_b * cell.Volumn;
        }
    }

}