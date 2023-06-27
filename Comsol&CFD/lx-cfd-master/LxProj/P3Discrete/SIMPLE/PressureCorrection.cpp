#include "PressureCorrection.h"

namespace LxCFD
{
    void PressureCorrection::CheckCreate(FvZone &zone)
    {
        PressureCorrectionBasic::CheckCreate(zone);
        LxTool::CheckCreateVector(PhyFaces, Faces->size());
    }

    void PressureCorrection::Setb_Step1_Cor(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b_FaceCommon->at(i1) = Density->GetFaceValue(i1) * PhyFaces->at(i1).CalNonOrthogonalityCorrection_inner(Faces->at(i1), *Grad, *x);
        }
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            Set_bFaceCommon_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            Set_bFaceCommon_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            Set_bFaceCommon_0(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->PressureInOuts)
        {
            set_b_bound(*b->ThreadIndex, taskIndex);
        }
    }

    void PressureCorrection::Setb_Step2_Cor(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b->at(i1) = -MassImbalance->at(i1) + Cells->at(i1).CalIfOwnerAddElseMunus(*b_FaceCommon);
        }
    }

    void PressureCorrection::set_ALU_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            auto &mface = PhyFaces->at(i1);
            Vector3d Df_average = face.CalAverage(*Dc);
            mface.SetFace(face, Df_average);
            ALUO->at(i1) = ALUN->at(i1) = -Density->GetFaceValue(i1) * mface.gDiff;
        }
    }
    void PressureCorrection::set_ALU_bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            auto &mface = PhyFaces->at(i1);
            Vector3d Df_average = Dc->at(face.OSideCell);
            mface.SetFace(face, Df_average);
            ALUO->at(i1) = ALUN->at(i1) = -Density->GetFaceValue(i1) * mface.gDiff;
        }
    }

    void PressureCorrection::set_b_bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b_FaceCommon->at(i1) = Density->GetFaceValue(i1) * PhyFaces->at(i1).CalNonOrthogonalityCorrection_bound(Faces->at(i1), *Grad, *x);
        }
    }

    void PressureCorrection::addPressureCorrectionToMassFlux_inner(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d gradPf = face.CalCFCorrectedGradient_inner(*Grad, *x);
            double vf = Vector3d::DotProduct(PhyFaces->at(i1).Normal, gradPf); // Vector3d.DotProduct(Vector3d.XXYYZZProduct(Df_average, gradPf), face.Normal);//P596
            MassFlux->at(i1) -= Density->GetFaceValue(i1) * vf;
        }
    }

    void PressureCorrection::addPressureCorrectionToMassFlux_bound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d gradPf = face.CalCFCorrectedGradient_bound(*Grad, *x);
            double vf = Vector3d::DotProduct(PhyFaces->at(i1).Normal, gradPf); // Vector3d.DotProduct(Vector3d.XXYYZZProduct(Df_average, gradPf), face.Normal);//P596
            MassFlux->at(i1) -= Density->GetFaceValue(i1) * vf;
        }
    }
}