#include "PossionEquationBase.h"

namespace LxCFD
{
    void PossionEquationBase::setBound_flux0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            ALUO->at(i1) = ALUN->at(i1) = 0;
            b_FaceCommon->at(i1) = 0;
        }
    }
    void PossionEquationBase::setBound_flux(IndexNumber &indexNumber, ValueBase<double> *flux, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        if (Value1Base<double>* flux1 = dynamic_cast<Value1Base<double> *>(flux))
        {
            for (; i1 < endp1; ++i1)
            {
                FvFace &face = Faces->at(i1);
                ALUO->at(i1) = ALUN->at(i1) = 0;
                double fluxValue = flux1->GetFaceValue(i1) * face.Area;
                b_FaceCommon->at(i1) = fluxValue;

                Vector3d v = face.Normal - face.GetgT() * face.OToN;
                double svv = Vector3d::DotProduct(face.Normal, v) / Cells->at(face.OSideCell).Volumn;
                b->at(face.NSideCell) = fluxValue / Gamma->GetFaceValue(i1) - Vector3d::DotProduct(Grad->at(face.OSideCell), v) + svv * x->at(face.NSideCell);
                ADiag->at(face.NSideCell) = svv + face.GetgT();
            }
        }
        else if (Value2Base<double> * flux2 = dynamic_cast<Value2Base<double> *>(flux))
        {
            for (; i1 < endp1; ++i1)
            {
                FvFace &face = Faces->at(i1);
                ALUO->at(i1) = 0;
                double sa, sb;
                flux2->GetFaceValue(sa, sb, i1);
                sa *= face.Area;
                sb *= face.Area;
                b_FaceCommon->at(i1) = sb + sa * (x->at(face.NSideCell) - x->at(face.OSideCell));
                ALUN->at(i1) = sa;

                Vector3d v = face.Normal - face.GetgT() * face.OToN;
                double svv = Vector3d::DotProduct(face.Normal, v) / Cells->at(face.OSideCell).Volumn;
                double gamma = Gamma->GetFaceValue(i1);
                b->at(face.NSideCell) = sb / gamma - Vector3d::DotProduct(Grad->at(face.OSideCell), v) + svv * x->at(face.NSideCell);
                ADiag->at(face.NSideCell) = svv + face.GetgT() - sa / gamma;
            }
        }
    }
    void PossionEquationBase::updateBound_flux(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            x->at(face.NSideCell) = (b->at(face.NSideCell) + face.GetgT() * x->at(face.OSideCell)) / ADiag->at(face.NSideCell);
        }
    }

    void PossionEquationBase::updateBound_fixhFixT(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            x->at(face.NSideCell) = (b->at(face.NSideCell) - x->at(face.NSideCell) * x->at(face.OSideCell)) / ADiag->at(face.NSideCell);
        }
    }

    void PossionEquationBase::setBound_fixhFixT(IndexNumber &indexNumber, Value1Base<double> &fixh, Value1Base<double> &fixT, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            double hS = fixh.GetFaceValue(i1) * face.Area;
            double hS_div_gamma = hS / Gamma->GetFaceValue(i1);
            double PhiInf = fixT.GetFaceValue(i1);
            double FluxCb = hS * face.gDiff / (hS_div_gamma + face.gDiff);
            ALUN->at(i1) = -FluxCb; //会被加到ADiag
            ALUO->at(i1) = 0;
            b_FaceCommon->at(i1) = FluxCb * PhiInf + hS * face.CalNonOrthogonalityCorrection_bound(*Grad, *x) / (hS_div_gamma + face.gDiff);

            double xn_xo = x->at(face.NSideCell) - x->at(face.OSideCell);
            Vector3d v = face.Normal - face.GetgT() * face.OToN;
            double svv = Vector3d::DotProduct(face.Normal, v) / Cells->at(face.OSideCell).Volumn;
            b->at(face.NSideCell) = hS_div_gamma * PhiInf - (Vector3d::DotProduct(Grad->at(face.OSideCell), v) - svv * xn_xo);
            double atemp = svv + face.GetgT();
            ADiag->at(face.NSideCell) = atemp + hS_div_gamma;
            x->at(face.NSideCell) = -atemp;
        }
    }

    void PossionEquationBase::setAb_step1_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            ALUO->at(i1) = ALUN->at(i1) = -gamma * face.gDiff;
            b_FaceCommon->at(i1) = gamma * face.CalNonOrthogonalityCorrection_inner(*Grad, *x);
        }
    }

    void PossionEquationBase::setAb_step1_bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            double gamma = Gamma->GetFaceValue(i1);
            ALUO->at(i1) = ALUN->at(i1) = -gamma * face.gDiff;
            b_FaceCommon->at(i1) = gamma * face.CalNonOrthogonalityCorrection_bound(*Grad, *x);
        }
    }

    void PossionEquationBase::setAb_step2(Value2Base<double> &source2, int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvCell &cell = Cells->at(i1);
            double S_Ad, S_b;
            source2.GetCellValue(S_Ad, S_b, i1);
            ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO) - S_Ad * cell.Volumn;
            b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon) + S_b * cell.Volumn;
        }
    }

    void PossionEquationBase::setAb_step2(Value1Base<double> &source1, int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        if (source1.IsEqual0())
        {
            for (; i1 < endp1; ++i1)
            {
                FvCell &cell = Cells->at(i1);
                ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO);
                b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon);
            }
        }
        else
        {
            for (; i1 < endp1; ++i1)
            {
                FvCell &cell = Cells->at(i1);
                ADiag->at(i1) = -cell.CalAllAdd(*ALUN, *ALUO);
                b->at(i1) = cell.CalIfOwnerAddElseMunus(*b_FaceCommon) + source1.GetCellValue(i1) * cell.Volumn;
            }
        }
    }

}