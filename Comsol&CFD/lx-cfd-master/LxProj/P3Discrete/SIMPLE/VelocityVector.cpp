#include "VelocityVector.h"
#include "FvZone.h"
#include "PressureSIMPLE.h"
#include "PressureCorrection.h"
namespace LxCFD
{
    void VelocityVector::NoSlipWall::SetParameter(std::shared_ptr<Value1Base<Vector3d>> boundaryVelocity)
    {
        BoundaryVelocity = boundaryVelocity;
        SetVelState.SetState(boundaryVelocity->IsConstant());
    }
    void VelocityVector::VelocityInlet::SetParameter(std::shared_ptr<Value1Base<Vector3d>> velocity)
    {
        Velocity = velocity;
        SetVelState.SetState(velocity->IsConstant());
    }
    void VelocityVector::PressureInOut::SetParameter(std::shared_ptr<Value1Base<double>> pressure, std::shared_ptr<Value1Base<Vector3d>> direction)
    {
        Pressure = pressure;
        Direction = direction;
        SetPressureState.SetState(Pressure->IsConstant());
    }
    VelocityVector::Value3dBoundInVel::Value3dBoundInVel(std::shared_ptr<Value1Base<double>> value, FvZone &zone)
    {
        Value = value;
        Faces = &zone.Faces;
        Cells = &zone.Cells;
    }
    Vector3d VelocityVector::Value3dBoundInVel::GetCellValue(int cellIndex)
    {
        FvFace &face = Faces->at(Cells->at(cellIndex).NFaces.at(0));
        return (-Value->GetCellValue(cellIndex) / face.Area) * face.Normal;
    }
    VelocityVector::Value3dBoundNormalDir::Value3dBoundNormalDir(FvZone &zone)
    {
        Faces = &zone.Faces;
    }
    Vector3d VelocityVector::Value3dBoundNormalDir::GetFaceValue(int faceIndex)
    {
        return Faces->at(faceIndex).Normal;
    }
    void VelocityVector::TransientVelocity::Create(LxCFD::VelocityVector *velocityVector)
    {
        this->VelocityVector = velocityVector;
        int facelength = velocityVector->Faces->size();
        LxTool::CheckCreateVector(RhoVel_o, facelength);
        LxTool::CheckCreateVector(RhoVel_oo, facelength);
        LxTool::CheckCreateVector(Vel_o, facelength);
        //TransientDataState = TransientDataStates.None;
    }
    void VelocityVector::TransientVelocity::SetTrans(std::shared_ptr<Value1Base<double>> density)
    {
        Density = density;
    }
    void VelocityVector::TransientVelocity::CheckCreateTransRhieChow()
    {
        if (IsSecondOrder && TransientDataState == TransientDataStates::Both_o_oo)
        {
            if (VelocityVector->VelocityDirectionCorrection == nullptr || typeid(*VelocityVector->VelocityDirectionCorrection) != typeid(RhieChow_2ndOrderTrans))
            {
                VelocityVector->VelocityInterpolation = std::unique_ptr<RhieChow_2ndOrderTrans>(new RhieChow_2ndOrderTrans());
                VelocityVector->VelocityInterpolation->SetParameter(PressureCor, Pressure);
            }
            auto *inter = dynamic_cast<RhieChow_2ndOrderTrans *>(VelocityVector->VelocityInterpolation.get());
            inter->RhoVel_o = this->RhoVel_o.get();
            inter->RhoVel_oo = this->RhoVel_oo.get();
            inter->Vel_o = this->Vel_o.get();
        }
        else
        {
            if (VelocityVector->VelocityDirectionCorrection == nullptr || typeid(*VelocityVector->VelocityDirectionCorrection) != typeid(RhieChow_1stOrderTrans))
            {
                VelocityVector->VelocityInterpolation = std::unique_ptr<RhieChow_1stOrderTrans>(new RhieChow_1stOrderTrans());
                VelocityVector->VelocityInterpolation->SetParameter(PressureCor, Pressure);
            }
            auto *inter = dynamic_cast<RhieChow_1stOrderTrans *>(VelocityVector->VelocityInterpolation.get());
            inter->RhoVel_o = this->RhoVel_o.get();
            inter->Vel_o = this->Vel_o.get();
        }
    }

    void VelocityVector::TransientVelocity::Initialize()
    {
        MultiThreads::RunCalTasks([this](int i)
                                  { save0(i); });
    }
    void VelocityVector::TransientVelocity::PrepareToSave()
    {
        std::shared_ptr<std::vector<Vector3d>> temp = RhoVel_o;
        RhoVel_o = RhoVel_oo;
        RhoVel_oo = temp;
        switch (TransientDataState)
        {
        case TransientDataStates::None:
            TransientDataState = TransientDataStates::Only_o;
            break;
        case TransientDataStates::Only_o:
            TransientDataState = TransientDataStates::Both_o_oo;
            break;
        default:
            break;
        }
        CheckCreateTransRhieChow();
    }

    void VelocityVector::TransientVelocity::SaveOldValue(int taskIndex)
    {
        saveOldValue(*VelocityVector->InnerIndex, taskIndex);
        for (auto &b : VelocityVector->PressureInOuts)
        {
            saveOldValue(*b->ThreadIndex, taskIndex);
        }
    }
    void VelocityVector::TransientVelocity::saveOldValue(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            RhoVel_o->at(i1) = Density->GetFaceValue(i1) * Vel_o->at(i1);
        }
    }

    void VelocityVector::TransientVelocity::save0(int taskIndex)
    {
        int i1, endp1;
        VelocityVector->TotalIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            RhoVel_o->at(i1) = Vector3d();
        }
    }
    Vector3d VelocityVector::GetVelocity(int cellIndex)
    {
        return Vector3d(U_x->at(cellIndex), V_x->at(cellIndex), W_x->at(cellIndex));
    }
    void VelocityVector::CheckCreate(FvZone &zone)
    {
        MassFluxBase::CheckCreate(zone);

        U_bFaceCommon = &zone.FaceCommonArray;
        LxTool::CheckCreateVector(V_bFaceCommon, Faces->size());
        LxTool::CheckCreateVector(W_bFaceCommon, Faces->size());

        if (U == nullptr)
        {
            U = std::unique_ptr<NSEquation>(new NSEquation());
            U->CheckCreate(zone);
        }
        U_x = U->x.get();
        U->b_FaceCommon = U_bFaceCommon;
        if (V == nullptr)
        {
            V = std::unique_ptr<NSEquation>(new NSEquation());
            V->CheckCreate(zone);
        }
        V_x = V->x.get();
        V->b_FaceCommon = V_bFaceCommon.get();
        if (W == nullptr)
        {
            W = std::unique_ptr<NSEquation>(new NSEquation());
            W->CheckCreate(zone);
        }
        W_x = W->x.get();
        W->b_FaceCommon = W_bFaceCommon.get();
    }
    void VelocityVector::SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> UVW_gamma, std::shared_ptr<Value1Base<double>> dynamicViscosity, std::shared_ptr<ValueBase<Vector3d>> UVW_source, std::shared_ptr<Value1Base<Vector3d>> UVW_iniValue, double UVW_relaxFactor)
    {
        NoSlipWalls.clear();
        Symmetries.clear();
        VelocityInlets.clear();
        PressureInOuts.clear();

        UVW_Gamma = UVW_gamma;
        DynamicViscosity = dynamicViscosity;
        UVW_Source = UVW_source;
        UVW_IniValue = UVW_iniValue;
        UVW_RelaxFactor = UVW_relaxFactor;

        U->SetZone_CommonTerm(UVW_Gamma, Value1Const::Double0, nullptr, UVW_RelaxFactor);
        V->SetZone_CommonTerm(UVW_Gamma, Value1Const::Double0, nullptr, UVW_RelaxFactor);
        W->SetZone_CommonTerm(UVW_Gamma, Value1Const::Double0, nullptr, UVW_RelaxFactor);
    }
    void VelocityVector::SetZone_ConvTerm(std::shared_ptr<Value1Base<double>> density, ConvectionSchemes convectionSchemes)
    {
        Density = density;
        U->SetZone_ConvTerm(Value1Const::Double1, convectionSchemes, *this);
        V->SetZone_ConvTerm(Value1Const::Double1, convectionSchemes, *this);
        W->SetZone_ConvTerm(Value1Const::Double1, convectionSchemes, *this);
    }
    void VelocityVector::SetBoundary_NoSlipMovingWall(std::shared_ptr<Value1Base<Vector3d>> boundaryVelocity, FvThread &thread)
    {
        std::unique_ptr<NoSlipWall> noSlipWall = std::unique_ptr<NoSlipWall>(new NoSlipWall());
        noSlipWall->SetHead(thread);
        noSlipWall->SetParameter(boundaryVelocity);
        NoSlipWalls.push_back(std::move(noSlipWall));

        U->SetBoundary_symmetry(thread);
        V->SetBoundary_symmetry(thread);
        W->SetBoundary_symmetry(thread);
    }
    void VelocityVector::SetBoundary_NoSlipStaticWall(FvThread &thread)
    {
        SetBoundary_NoSlipMovingWall(Value1Const::Vector0, thread);
    }
    void VelocityVector::SetBoundary_SlipWall(FvThread &thread)
    {
        auto boundarySlipWall = std::unique_ptr<Symmetry>(new Symmetry());
        boundarySlipWall->SetHead(thread);
        Symmetries.push_back(std::move(boundarySlipWall));

        U->SetBoundary_symmetry(thread);
        V->SetBoundary_symmetry(thread);
        W->SetBoundary_symmetry(thread);
    }
    void VelocityVector::SetBound_VelocityInlet(std::shared_ptr<Value1Base<Vector3d>> value3d, FvThread &thread)
    {
        auto velinlet = std::unique_ptr<VelocityInlet>(new VelocityInlet());
        velinlet->SetHead(thread);
        velinlet->SetParameter(value3d);
        VelocityInlets.push_back(std::move(velinlet));

        U->SetBoundary_flow(nullptr, thread);
        V->SetBoundary_flow(nullptr, thread);
        W->SetBoundary_flow(nullptr, thread);
    }
    void VelocityVector::SetBound_VelocityInlet(std::shared_ptr<Value1Base<double>> value, FvThread &thread) //方向垂直壁面指向域内
    {
        SetBound_VelocityInlet(std::shared_ptr<Value3dBoundInVel>(new Value3dBoundInVel(value, *Zone)), thread);
    }
    void VelocityVector::SetBound_PressureInOut(std::shared_ptr<Value1Base<double>> pressure, std::shared_ptr<Value1Base<Vector3d>> direction, FvThread &thread)
    {
        auto pressureinout = std::unique_ptr<PressureInOut>(new PressureInOut());
        pressureinout->SetHead(thread);
        pressureinout->SetParameter(pressure, direction);
        PressureInOuts.push_back(std::move(pressureinout));

        U->SetBoundary_flow(nullptr, thread);
        V->SetBoundary_flow(nullptr, thread);
        W->SetBoundary_flow(nullptr, thread);
    }
    void VelocityVector::SetBound_PressureInOut(std::shared_ptr<Value1Base<double>> pressure, FvThread &thread) //方向垂直壁面指向域内
    {
        auto dir = std::shared_ptr<Value3dBoundNormalDir>(new Value3dBoundNormalDir(*Zone));
        SetBound_PressureInOut(pressure, dir, thread);
    }
    void VelocityVector::Initialize()
    {
        MultiThreads::RunCalTasks([this](int i)
                                  { initialize(i); });
    }

    void VelocityVector::initialize(int taskIndex)
    {
        setUVW_x(*UVW_IniValue, *InnerIndex, taskIndex);
        SetUVW_x(taskIndex);
        for (auto &b : Symmetries)
        {
            set_x_SlipWall(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : PressureInOuts)
        {
            setUVW_x(*UVW_IniValue, *b->ThreadIndex, taskIndex);
        }
        //重置mass相关
        CalFaceMassFlux(taskIndex);
        CalMassImbalance(taskIndex);
        // setFaceFlux_0(*TotalIndex, taskIndex);
        // setMassImbanlance_0(*TotalIndex, taskIndex);
    }
    void VelocityVector::SetUVW_x(int taskIndex)
    {
        for (auto &b : NoSlipWalls)
        {
            if (b->SetVelState.GetIsNeedToCal(taskIndex))
            {
                if (b->BoundaryVelocity->IsEqual0())
                {
                    setUVW_x(*b->BoundaryVelocity, *b->ThreadIndex, taskIndex);
                }
                else
                {
                    set_x_MovingWall(*b->BoundaryVelocity, *b->ThreadIndex, taskIndex);
                }
            }
        }
        for (auto &b : VelocityInlets)
        {
            if (b->SetVelState.GetIsNeedToCal(taskIndex))
            {
                setUVW_x(*b->Velocity, *b->ThreadIndex, taskIndex);
            }
        }
    }

    void VelocityVector::AddViscositySource_LoopFace(int taskIndex) //由于每个线程处理的index是固定的，不需要考虑同步的问题
    {
        //由于粘性导致的Source
        addFaceViscositySource_inner(taskIndex);
        for (auto &b : NoSlipWalls)
        {
            addUVW_Ab_WallShearStress(*b->ThreadIndex, taskIndex); //不采用fixValue的形式，可以实现层流与湍流的通用性，按理说还得添加垂直壁面方向的力，没有加
            addUVW_Ab_NormalStress(*DynamicViscosity, *b->ThreadIndex, taskIndex);
        }
        for (auto &b : Symmetries)
        {
            addUVW_Ab_NormalStress(*UVW_Gamma, *b->ThreadIndex, taskIndex);
        }
        for (auto &b : VelocityInlets)
        {
            addFaceViscositySource_boundOwner(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : PressureInOuts)
        {
            addFaceViscositySource_boundOwner(*b->ThreadIndex, taskIndex);
        }
    }
    void VelocityVector::AddSource_LoopCell(int taskIndex)
    {
        //附加的Source,Scalar中的Source
        Add_bSource(UVW_Source.get(), *InnerIndex, taskIndex);
    }

    void VelocityVector::UpdateUVWBound(int taskIndex)
    {
        for (auto &b : Symmetries)
        {
            set_x_SlipWall(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : PressureInOuts)
        {
            set_x_pressureBound(*b->Direction, *b->ThreadIndex, taskIndex);
        }

        //调试用
        for (int i1 = InnerIndex->FaceIDs.End + 1; i1 <= TotalIndex->FaceIDs.End; ++i1)
        {
            FvFace &face = Faces->at(i1);
            MassImbalance->at(face.NSideCell) = MassImbalance->at(face.OSideCell);
        }
    }

    void VelocityVector::CalResidual(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        double maxFaceFlux = 0, maxImbalance = 0;
        for (; i1 < endp1; i1++)
        {
            auto &m = MassImbalance->at(i1);
            if (m > maxImbalance)
                maxImbalance = m;
        }
        TotalIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            auto &m = MassFlux->at(i1);
            if (m > maxFaceFlux)
                maxFaceFlux = m;
        }
        ThreadsMath::KeepMax(Max_Rc, maxImbalance);
        ThreadsMath::KeepMax(Max_acPhic, maxFaceFlux);
    }

    void VelocityVector::GetResidual_Reset(double &out_Rc, double &out_acPhic)
    {
        out_Rc = Max_Rc;
        out_acPhic = Max_acPhic;
        Max_Rc = 0;
        Max_acPhic = 0;
    }
    void VelocityVector::CalFaceMassFlux(int taskIndex)
    {
        calFaceMassFlux_inner(taskIndex);
        for (auto &b : NoSlipWalls)
        {
            setWallFlux0(*b, taskIndex);
        }
        for (auto &b : Symmetries)
        {
            setWallFlux0(*b, taskIndex);
        }
        for (auto &b : VelocityInlets)
        {
            calFaceMassFlux_VelBound(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : PressureInOuts)
        {
            calFaceMassFlux_pressureBound(*b->ThreadIndex, taskIndex);
        }
    }
    void VelocityVector::SetZone_TransTerm(bool isEnable, std::shared_ptr<Value1Base<double>> Trans, std::shared_ptr<Value1Base<double>> density)
    {
        U->SetZone_TransTerm(isEnable, Trans, density);
        V->SetZone_TransTerm(isEnable, Trans, density);
        W->SetZone_TransTerm(isEnable, Trans, density);
        if (isEnable)
        {
            if (TransVelData == nullptr)
            {
                TransVelData = std::unique_ptr<TransientVelocity>(new TransientVelocity());
                TransVelData->Create(this);
            }
            TransVelData->SetTrans(density);
        }
        else
        {
            TransVelData = nullptr;
        }
    }
    void VelocityVector::SetZone_RhieChow_AfterSetTrans(PressureCorrectionBasic *pressureCorInSIMPLE, PressureSIMPLE *pressureInSIMPLE)
    {
        if (TransVelData == nullptr)
        {
            if (VelocityInterpolation == nullptr || typeid(*VelocityInterpolation) != typeid(RhieChowInterpolation))
            {
                VelocityInterpolation = std::unique_ptr<RhieChowInterpolation>(new RhieChowInterpolation());
            }
            VelocityInterpolation->SetParameter(pressureCorInSIMPLE, pressureInSIMPLE);
        }
        else
        {
            TransVelData->PressureCor = pressureCorInSIMPLE;
            TransVelData->Pressure = pressureInSIMPLE;
            TransVelData->CheckCreateTransRhieChow();
        }
    }
    void VelocityVector::setUVW_x(Value1Base<Vector3d> &UVWValue, IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            Vector3d v = UVWValue.GetCellValue(i1);
            U_x->at(i1) = v.X;
            V_x->at(i1) = v.Y;
            W_x->at(i1) = v.Z;
        }
    }
    void VelocityVector::set_x_MovingWall(Value1Base<Vector3d> &UVWValue, IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d v = UVWValue.GetCellValue(face.NSideCell);
            v = Vector3d::VectorToPlane(v, face.Normal);
            U_x->at(face.NSideCell) = v.X;
            V_x->at(face.NSideCell) = v.Y;
            W_x->at(face.NSideCell) = v.Z;
        }
    }
    void VelocityVector::set_x_SlipWall(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d v = GetVelocity(face.OSideCell);
            v = Vector3d::VectorToPlane(v, face.Normal);
            U_x->at(face.NSideCell) = v.X;
            V_x->at(face.NSideCell) = v.Y;
            W_x->at(face.NSideCell) = v.Z;
        }
    }

    void VelocityVector::set_x_pressureBound(Value1Base<Vector3d> &direction, IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            //要区分流出还是流入
            double massflux = MassFlux->at(i1);
            if (massflux > 0) ////由明确的流出时，确定为流出边界
            {
                U->CalBoundValue_grad0(face);
                V->CalBoundValue_grad0(face);
                W->CalBoundValue_grad0(face);
            }
            else
            {
                Vector3d dir = direction.GetFaceValue(i1);
                double des = Density->GetFaceValue(i1);
                double evsb = Vector3d::DotProduct(dir, face.Normal);
                if (evsb != 0)
                {
                    double massb = massflux;
                    Vector3d v = massb / (des * evsb) * dir;
                    U_x->at(face.NSideCell) = v.X;
                    V_x->at(face.NSideCell) = v.Y;
                    W_x->at(face.NSideCell) = v.Z;
                }
                else
                {
                    LxConsole::Error("压力边界所指定的速度方向不指向区域内");
                }
            }
        }
    }

    void VelocityVector::Add_bSource(ValueBase<Vector3d> *S_Value3d, IndexNumber &indexNumber, int taskIndex)
    {
        auto &U_ADiag = *U->ADiag;
        auto &U_b = *U->b;
        auto &V_ADiag = *V->ADiag;
        auto &V_b = *V->b;
        auto &W_ADiag = *W->ADiag;
        auto &W_b = *W->b;
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        if (auto *s3d1 = dynamic_cast<Value1Base<Vector3d> *>(S_Value3d))
        {
            if (s3d1->IsEqual0())
                return;
            for (; i1 < endp1; ++i1)
            {
                Vector3d v = s3d1->GetCellValue(i1);
                v *= (Cells->at(i1).Volumn);
                U_b.at(i1) += v.X;
                V_b.at(i1) += v.Y;
                W_b.at(i1) += v.Z;
            }
        }
        else if (auto *s3d2 = dynamic_cast<Value2Base<Vector3d> *>(S_Value3d))
        {
            for (; i1 < endp1; ++i1)
            {
                double volumn = Cells->at(i1).Volumn;
                Vector3d va, vb;
                s3d2->GetCellValue(va, vb, i1);
                va *= (volumn);
                vb *= (volumn);
                U_b.at(i1) += vb.X;
                V_b.at(i1) += vb.Y;
                W_b.at(i1) += vb.Z;
                U_ADiag.at(i1) -= va.X;
                V_ADiag.at(i1) -= va.Y;
                W_ADiag.at(i1) -= va.Z;
            }
        }
        else
        {
            LxConsole::Error("速度矢量场无法识别源项");
        }
    }

    void VelocityVector::addFaceViscositySource_inner(int taskIndex)
    {
        auto &U_grad = *U->Grad;
        auto &U_bFaceCommon = *U->b_FaceCommon;
        auto &V_grad = *V->Grad;
        auto &V_bFaceCommon = *V->b_FaceCommon;
        auto &W_grad = *W->Grad;
        auto &W_bFaceCommon = *W->b_FaceCommon;
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d dU = face.CalCFCorrectedGradient_inner(U_grad, *U_x);
            Vector3d dV = face.CalCFCorrectedGradient_inner(V_grad, *V_x);
            Vector3d dW = face.CalCFCorrectedGradient_inner(W_grad, *W_x);
            double gamma = UVW_Gamma->GetFaceValue(i1);
            U_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.X, dV.X, dW.X), face.Normal);
            V_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.Y, dV.Y, dW.Y), face.Normal);
            W_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.Z, dV.Z, dW.Z), face.Normal);
        }
    }

    void VelocityVector::addFaceViscositySource_boundOwner(IndexNumber &indexNumber, int taskIndex)
    {
        auto &U_grad = *U->Grad;
        auto &U_bFaceCommon = *U->b_FaceCommon;
        auto &V_grad = *V->Grad;
        auto &V_bFaceCommon = *V->b_FaceCommon;
        auto &W_grad = *W->Grad;
        auto &W_bFaceCommon = *W->b_FaceCommon;
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d dU = face.CalCFCorrectedGradient_bound(U_grad, *U_x);
            Vector3d dV = face.CalCFCorrectedGradient_bound(V_grad, *V_x);
            Vector3d dW = face.CalCFCorrectedGradient_bound(W_grad, *W_x);
            double gamma = UVW_Gamma->GetFaceValue(i1);
            U_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.X, dV.X, dW.X), face.Normal);
            V_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.Y, dV.Y, dW.Y), face.Normal);
            W_bFaceCommon.at(i1) += gamma * Vector3d::DotProduct(Vector3d(dU.Z, dV.Z, dW.Z), face.Normal);
        }
    }

    void VelocityVector::addUVW_Ab_WallShearStress(IndexNumber &indexNumber, int taskIndex)
    {
        auto &U_ALUN = *U->ALUN;
        auto &U_bFaceCommon = *U->b_FaceCommon;
        auto &V_ALUN = *V->ALUN;
        auto &V_bFaceCommon = *V->b_FaceCommon;
        auto &W_ALUN = *W->ALUN;
        auto &W_bFaceCommon = *W->b_FaceCommon;
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            Vector3d ov = GetVelocity(face.OSideCell);
            Vector3d nv = GetVelocity(face.NSideCell);
            double XX = LxTool::Pow2(face.Normal.X);
            double YY = LxTool::Pow2(face.Normal.Y);
            double ZZ = LxTool::Pow2(face.Normal.Z);
            double XY = face.Normal.X * face.Normal.Y;
            double YZ = face.Normal.Y * face.Normal.Z;
            double XZ = face.Normal.X * face.Normal.Z;
            double commonterm = UVW_Gamma->GetFaceValue(i1) / Vector3d::DotProduct(face.OToN, face.Normal);
            double temp = YY + ZZ;
            U_ALUN[i1] -= commonterm * (temp);
            U_bFaceCommon[i1] += commonterm * (nv.X * (temp) + (ov.Y - nv.Y) * XY + (ov.Z - nv.Z) * XZ);
            temp = XX + ZZ;
            V_ALUN[i1] -= commonterm * (temp);
            V_bFaceCommon[i1] += commonterm * ((ov.X - nv.X) * XY + nv.Y * (temp) + (ov.Z - nv.Z) * YZ);
            temp = XX + YY;
            W_ALUN[i1] -= commonterm * (temp);
            W_bFaceCommon[i1] += commonterm * ((ov.X - nv.X) * XZ + (ov.Y - nv.Y) * YZ + nv.Z * (temp));
        }
    }

    void VelocityVector::addUVW_Ab_NormalStress(Value1Base<double> &gamma, IndexNumber &indexNumber, int taskIndex)
    {
        auto &U_ALUN = *U->ALUN;
        auto &U_bFaceCommon = *U->b_FaceCommon;
        auto &V_ALUN = *V->ALUN;
        auto &V_bFaceCommon = *V->b_FaceCommon;
        auto &W_ALUN = *W->ALUN;
        auto &W_bFaceCommon = *W->b_FaceCommon;
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d ov = GetVelocity(face.OSideCell);
            double common = 2 * gamma.GetFaceValue(i1) / Vector3d::DotProduct(face.OToN, face.Normal);
            U_ALUN.at(i1) -= common * LxTool::Pow2(face.Normal.X);
            U_bFaceCommon.at(i1) -= common * (ov.Y * face.Normal.Y + ov.Z * face.Normal.Z) * face.Normal.X;
            V_ALUN.at(i1) -= common * LxTool::Pow2(face.Normal.Y);
            V_bFaceCommon.at(i1) -= common * (ov.X * face.Normal.X + ov.Z * face.Normal.Z) * face.Normal.Y;
            W_ALUN.at(i1) -= common * LxTool::Pow2(face.Normal.Z);
            W_bFaceCommon.at(i1) -= common * (ov.X * face.Normal.X + ov.Y * face.Normal.Y) * face.Normal.Z;
        }
    }
    void VelocityVector::setWallFlux0(Wall &b, int taskIndex)
    {
        if (b.FluxState.GetIsNeedToCal(taskIndex))
        {
            setFaceFlux_0(*b.ThreadIndex, taskIndex);
        }
    }
    void VelocityVector::calFaceMassFlux_VelBound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d vf = GetVelocity(face.NSideCell); //不进行修正，因为压力本身是根据内部网格计算出来的，不会出现棋盘型问题，且这样保证流入的质量一定等于速度乘以面积
            MassFlux->at(i1) = Density->GetFaceValue(i1) * Vector3d::DotProduct(vf, face.Normal);
        }
    }

    void VelocityVector::calFaceMassFlux_inner(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d v_O = GetVelocity(face.OSideCell);
            Vector3d v_N = GetVelocity(face.NSideCell);
            Vector3d vf = (1 - face.gOwner) * v_O + face.gOwner * v_N + VelocityInterpolation->CalVelocityCorrection_Inner(i1, face);
            double des = Density->GetFaceValue(i1);
            MassFlux->at(i1) = des * Vector3d::DotProduct(vf, face.Normal);
            VelocityDirectionCorrection->at(i1) = calVelocityDirectionCorrecion(v_O, v_N, vf, face, des);
        }
    }

    void VelocityVector::calFaceMassFlux_pressureBound(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; i1++)
        {
            FvFace &face = Faces->at(i1);
            Vector3d v_O = GetVelocity(face.OSideCell);
            //Vector3d v_N = getVelocity(face.NSideCell);
            Vector3d vf = v_O + VelocityInterpolation->CalVelocityCorrection_Bound(i1, face);
            double des = Density->GetFaceValue(i1);
            MassFlux->at(i1) = des * Vector3d::DotProduct(vf, face.Normal);
            //VelDirCor应该不用修正，因为用不到
        }
    }

    float VelocityVector::calVelocityDirectionCorrecion(Vector3d &v_O, Vector3d &v_N, Vector3d &vf, FvFace &face, double density)
    {
        //0为没有修正
        double vo2 = v_O.CalLengthSquared();
        double vn2 = v_N.CalLengthSquared();
        if (vo2 > 1e-100 && vn2 > 1e-100)
        {
            double cosa = Vector3d::DotProduct(v_O, v_N) / std::sqrt(vo2 * vn2);
            return (float)std::fabs((1 - cosa) * density * Vector3d::DotProduct(vf, face.OToN)); //* 0.5
        }
        else
        {
            return 0; // (float)(density.getFaceValue(faceIndex) * Vector3d.DotProduct(vf, face.OwnerToNeighbor));
        }
    }
}