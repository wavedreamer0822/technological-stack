#include "PressureCorrectionBasic.h"

namespace LxCFD
{
    void PressureCorrectionBasic::CheckCreate(FvZone &zone)
    {
        EquationBase::CheckCreate(zone);
        LxTool::CheckCreateVector(Dc, Cells->size());
    }

    void PressureCorrectionBasic::SetZone(double pressureRelaxFactor, SIMPLEMethods solvingMethod, LxCFD::VelocityVector *velocityVector, LxCFD::PressureSIMPLE *pressureInSimple, std::shared_ptr<Value1Base<double>> density)
    {
        clear_eFlags();
        RelaxFactor = pressureRelaxFactor;
        SIMPLEMethod = solvingMethod;

        VelocityVector = velocityVector;
        MassFlux = velocityVector->MassFlux.get();
        MassImbalance = velocityVector->MassImbalance.get();

        PressureSIMPLE = pressureInSimple;
        Pressure = pressureInSimple->x.get();

        Density = density;
    }

    void PressureCorrectionBasic::SetBound_AfterSettingVelocityVector()
    {
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            e_ALUO0.push_back(b->ThreadID);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            e_ALUO0.push_back(b->ThreadID);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            e_ALUO0.push_back(b->ThreadID);
        }
        for (auto &b : VelocityVector->PressureInOuts)
        {
            e_FixValue.push_back(b->ThreadID);
        }
    }

    void PressureCorrectionBasic::Set_x_Bound(int taskIndex) //压力修正初始值都为0
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            x->at(i1) = 0;
        }
    }

    void PressureCorrectionBasic::SetAb_Step1(int taskIndex)
    {
        set_ALU_inner(taskIndex);
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            set_ALU_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            set_ALU_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            set_ALU_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->PressureInOuts)
        {
            set_ALU_bound(*b->ThreadIndex, taskIndex);
        }
    }

    void PressureCorrectionBasic::SetAb_Step2(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b->at(i1) = -MassImbalance->at(i1);
            ADiag->at(i1) = -Cells->at(i1).CalAllAdd(*ALUN, *ALUO);
        }
    }

    void PressureCorrectionBasic::SetAb_PCor0Point(int CellIndex)
    {
        FvCell &cell = Cells->at(CellIndex);
        for (auto &f : cell.OFaces)
        {
            ALUO->at(f) = 0;
        }
        for (auto &f : cell.NFaces)
        {
            ALUN->at(f) = 0;
        }
        b->at(CellIndex) = 0;
    }
    void PressureCorrectionBasic::Update_x_Bound(int taskIndex)
    {
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            predict_Bound(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            predict_Bound(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            predict_Bound(*b->ThreadIndex, taskIndex);
        }
    }

    void PressureCorrectionBasic::ApplyPCorToUVWP(int taskIndex)
    {
        addCorrectionToUVW(*InnerIndex, taskIndex);
        addCorrectionToPressure(*InnerIndex, taskIndex);
        addPressureCorrectionToMassFlux_inner(*InnerIndex, taskIndex);
        for (auto &b : VelocityVector->PressureInOuts)
        {
            addPressureCorrectionToMassFlux_bound(*b->ThreadIndex, taskIndex);
        }
    }

    void PressureCorrectionBasic::ApplyPCorToUVWP_NoRelax(int taskIndex)
    {
        addCorrectionToUVW(*InnerIndex, taskIndex);
        addCorrectionToPressure_NoRelax(*InnerIndex, taskIndex);
        addPressureCorrectionToMassFlux_inner(*InnerIndex, taskIndex);
        for (auto &b : VelocityVector->PressureInOuts)
        {
            addPressureCorrectionToMassFlux_bound(*b->ThreadIndex, taskIndex);
        }
    }

    void PressureCorrectionBasic::CalDc_ADiagNotRelaxed(int taskIndex) //如果U V W的系数矩阵未进行过松弛//添加源项可能改动A_Diag，所以计算完A_Diag后立即计算Dc
    {
        auto &U_A_Diag = *VelocityVector->U->ADiag;
        auto &V_A_Diag = *VelocityVector->V->ADiag;
        auto &W_A_Diag = *VelocityVector->W->ADiag;
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double volumn = Cells->at(i1).Volumn;
            Dc->at(i1) = Vector3d(volumn / U_A_Diag.at(i1), volumn / V_A_Diag.at(i1), volumn / W_A_Diag.at(i1));
        }
    }

    void PressureCorrectionBasic::Setb_Step1_Cor(int taskIndex)
    {
        throw LxTool::GetNotImplementedException();
    }

    void PressureCorrectionBasic::Setb_Step2_Cor(int taskIndex)
    {
        throw LxTool::GetNotImplementedException();
    }

    void PressureCorrectionBasic::set_ALU_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        PhysicalFaceOverRelax mface;
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d Df_average = face.CalAverage(*Dc);
            mface.SetFace(face, Df_average);
            ALUO->at(i1) = ALUN->at(i1) = -Density->GetFaceValue(i1) * mface.gDiff;
        }
    }

    void PressureCorrectionBasic::set_ALU_bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        PhysicalFaceOverRelax mface;
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d &Df_average = Dc->at(face.OSideCell);
            mface.SetFace(face, Df_average);
            ALUO->at(i1) = ALUN->at(i1) = -Density->GetFaceValue(i1) * mface.gDiff;
        }
    }

    void PressureCorrectionBasic::predict_Bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            x->at(face.NSideCell) = x->at(face.OSideCell);
        }
    }

    void PressureCorrectionBasic::addCorrectionToUVW(IndexNumber &indexNumber, int taskIndex)
    {
        auto &U_x = *VelocityVector->U->x;
        auto &V_x = *VelocityVector->V->x;
        auto &W_x = *VelocityVector->W->x;
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            Vector3d velocityCorrection = Vector3d::XXYYZZProduct(Dc->at(i1), Grad->at(i1));
            U_x.at(i1) -= velocityCorrection.X;
            V_x.at(i1) -= velocityCorrection.Y;
            W_x.at(i1) -= velocityCorrection.Z;
        }
    }

    void PressureCorrectionBasic::addCorrectionToPressure(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            Pressure->at(i1) += RelaxFactor * x->at(i1);
        }
    }

    void PressureCorrectionBasic::addCorrectionToPressure_NoRelax(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            Pressure->at(i1) += x->at(i1);
        }
    }

    void PressureCorrectionBasic::addPressureCorrectionToMassFlux_inner(IndexNumber &indexNumber, int taskIndex) //需要对公式校核以下，这个公式理论上应与RhieChow一致
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d Df_average = face.CalAverage(*Dc);
            Vector3d gradPf = face.CalCFCorrectedGradient_inner(*Grad, *x);
            double vf = Vector3d::DotProduct(Vector3d::XXYYZZProduct(Df_average, gradPf), face.Normal); //P596
            MassFlux->at(i1) -= Density->GetFaceValue(i1) * vf;
        }
    }

    void PressureCorrectionBasic::addPressureCorrectionToMassFlux_bound(IndexNumber &indexNumber, int taskIndex) //需要对公式校核以下，这个公式理论上应与RhieChow一致
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d Df_average = Dc->at(face.OSideCell);
            Vector3d gradPf = face.CalCFCorrectedGradient_bound(*Grad, *x);
            double vf = Vector3d::DotProduct(Vector3d::XXYYZZProduct(Df_average, gradPf), face.Normal); //P620,公式是否正确？？？
            MassFlux->at(i1) -= Density->GetFaceValue(i1) * vf;
        }
    }
}