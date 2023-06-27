#include "PressureSIMPLE.h"
#include "FvZone.h"
#include "PressureCorrectionBasic.h"
namespace LxCFD
{
    void PressureSIMPLE::SetZone(std::shared_ptr<Value1Base<double>> iniValue, LxCFD::VelocityVector *velocityVector, PressureCorrectionBasic *Pcor, std::shared_ptr<Value1Base<double>> density)
    {
        IniValue = iniValue;

        VelocityVector = velocityVector;
        MassFlux = velocityVector->MassFlux.get();

        Dc = Pcor->Dc.get();

        Density = density;
    }

    void PressureSIMPLE::Initialize()
    {
        MultiThreads::RunCalTasks([this](int i)
                                  { initialize_Setx_CalCenter_step1(i); });
        double sum1, sum2, sum3;
        //计算中几何中心
        {

            ThreadsMath::GetSum(sum1, sum2, sum3);
            Center = Vector3d(sum1, sum2, sum3);
            Center *= (1 / Zone->Volumn);
            MinLength = std::numeric_limits<double>::max(); // double.MaxValue;
        }
        MultiThreads::RunCalTasks([this](int i)
                                  { initialize_step3(i); });
        //
        {
            ThreadsMath::GetSum(sum1, sum2, sum3);
            InitiialPressureProductBoundArea = sum1;
            BoundArea = 0;
            for (auto &b : Zone->BoundThreads)
            {
                BoundArea += b->Area;
            }
        }
    }
    void PressureSIMPLE::CalPressureArea(int taskIndex) //计算边界压力*面积
    {
        for (auto &b : Zone->BoundThreads)
        {
            int i1, endp1;
            b->ThreadIndex.FaceIDs.GetSeg(i1, endp1, taskIndex);
            double temp = 0;
            for (; i1 < endp1; ++i1)
            {
                FvFace &face = Faces->at(i1);
                temp += x->at(face.NSideCell) * face.Area;
            }
            ThreadsMath::AddToSum(temp);
        }
    }

    void PressureSIMPLE::CorrectPressureByReferenct(double pressureBoundCor, int taskIndex)
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            x->at(i1) += pressureBoundCor;
        }
    }

    void PressureSIMPLE::Predict_bound(int taskIndex)
    {
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            predict_bound_Wall(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            predict_bound_Wall(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            predict_bound_byMassFlux(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->PressureInOuts)
        {
            if (b->SetPressureState.GetIsNeedToCal(taskIndex))
            {
                set_x(*b->Pressure, *b->ThreadIndex, taskIndex);
            }
        }
    }

    void PressureSIMPLE::initialize_Setx_CalCenter_step1(int taskIndex)
    {
        set_x(*IniValue, *InnerIndex, taskIndex);
        for (auto &b : VelocityVector->NoSlipWalls)
        {
            set_x(*IniValue, *b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->Symmetries)
        {
            set_x(*IniValue, *b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->VelocityInlets)
        {
            set_x(*IniValue, *b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityVector->PressureInOuts)
        {
            if (b->SetPressureState.GetIsNeedToCal(taskIndex))
            {
                set_x(*b->Pressure, *b->ThreadIndex, taskIndex);
            }
        }
        //为了求中心，先求体积*坐标之和
        {
            int i1, endp1;
            InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
            Vector3d centerProductVolumn;
            for (; i1 < endp1; ++i1)
            {
                FvCell &cell = Cells->at(i1);
                centerProductVolumn += (cell.Volumn * cell.Center);
            }
            ThreadsMath::AddToSum(centerProductVolumn.X, centerProductVolumn.Y, centerProductVolumn.Z);
        }
    }

    void PressureSIMPLE::initialize_step3(int taskIndex) //和上面计算面积的要对应
    {
        CalPressureArea(taskIndex);
        //需要初始化梯度场
        CalGradient(taskIndex);
        //计算找到与几何中心最近的cell
        {
            int i1, endp1;
            InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
            double minLengthlocal = std::numeric_limits<double>::max(); // double.MaxValue;
            int minIndexLocal = 0;
            for (; i1 < endp1; ++i1)
            {
                double lengthtemp = (Cells->at(i1).Center - Center).CalLengthSquared();
                if (lengthtemp < minLengthlocal)
                {
                    minLengthlocal = lengthtemp;
                    minIndexLocal = i1;
                }
            }
            std::unique_lock<std::mutex> lock(MultiThreads::GlobalMutex);
            if (minLengthlocal < MinLength)
            {
                MinLength = minLengthlocal;
                CenterCellIndex = minIndexLocal;
            }
        }
    }

    void PressureSIMPLE::predict_bound_Wall(IndexNumber &indexNumber, int taskIndex) //方法2，精度更高，计算量大，对应P603（有修改，见笔记）
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            double fenzi = Vector3d::DotProduct(VelocityVector->GetVelocity(face.OSideCell), face.Normal) * face.OToN.CalLengthSquared(); //Dc已改为不包含relax的了
            double fenmu = Vector3d::DotProduct(Vector3d::XXYYZZProduct(Dc->at(face.OSideCell), face.OToN), face.Normal);
            x->at(face.NSideCell) = x->at(face.OSideCell) + Vector3d::DotProduct(Grad->at(face.OSideCell), face.OToN) + fenzi / fenmu;
        }
    }

    void PressureSIMPLE::predict_bound_byMassFlux(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            double fenzi = (Vector3d::DotProduct(VelocityVector->GetVelocity(face.OSideCell), face.Normal) - MassFlux->at(i1) / Density->GetFaceValue(i1)) * face.OToN.CalLengthSquared(); //Dc已改为不包含relax的了
            double fenmu = Vector3d::DotProduct(Vector3d::XXYYZZProduct(Dc->at(face.OSideCell), face.OToN), face.Normal);
            x->at(face.NSideCell) = x->at(face.OSideCell) + Vector3d::DotProduct(Grad->at(face.OSideCell), face.OToN) + fenzi / fenmu;
        }
    }

}