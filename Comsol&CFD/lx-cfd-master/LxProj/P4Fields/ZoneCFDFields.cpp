#include "ZoneCFDFields.h"
#include "FvZone.h"
#include "AppRes.h"
#include "Value1OppositeFromArray1.h"
#include "ValueListMaker.h"
#include "BoussinesqSource.h"
namespace LxCFD
{
    std::vector<double> *ZoneCFDFields::GetArray(ScalarTypes scalarTypes) const
    {
        switch (scalarTypes)
        {
        case ScalarTypes::Temperature:
            return T == nullptr ? nullptr : T->x.get();
        case ScalarTypes::MassImbalance:
            return Velocity == nullptr ? nullptr : Velocity->MassImbalance.get();
        case ScalarTypes::Vel_U:
            return Velocity == nullptr ? nullptr : Velocity->U->x.get();
        case ScalarTypes::Vel_V:
            return Velocity == nullptr ? nullptr : Velocity->V->x.get();
        case ScalarTypes::Vel_W:
            return Velocity == nullptr ? nullptr : Velocity->W->x.get();
        // case ScalarTypes.Turb_k:
        //     return kw ?.k.x;
        // case ScalarTypes.Turb_w:
        //     return kw ?.w.x;
        case ScalarTypes::Pressure:
            return P == nullptr ? nullptr : P->x.get();
        case ScalarTypes::PressureCorrection:
            return PCor == nullptr ? nullptr : PCor->x.get();
        default:
            return nullptr;
        }
    }
    void ZoneCFDFields::CheckCreate(FvZone *zone)
    {
        Zone = zone;
        PhysicalModel = zone->PhysicalModel.get();
        Material = PhysicalModel->MaterialData.get();
        if (PhysicalModel == nullptr || Material == nullptr)
        {
            throw std::invalid_argument("未设置区域的模型");
            return;
        }
        Density = Material->Density->GetCopy(zone);
        CheckCreate_Vel();
        CheckCreate_T();
        SetParameter_Vel();
        SetParameter_T();
    }
    void ZoneCFDFields::CheckCreate_T()
    {
        if (PhysicalModel->IsEnergyEnabled)
        {
            if (PhysicalModel->PhysicalType == PhysicalTypes::Solid)
            {
                if (T == nullptr || !(dynamic_cast<PossionEquation *>(T.get())))
                {
                    auto newT = std::unique_ptr<PossionEquation>(new PossionEquation());
                    newT->CopyFromOldEquation(std::move(T));
                    T = std::move(newT);
                    T->CheckCreate(*Zone);
                }
            }
            else
            {
                if (T == nullptr || !(dynamic_cast<NSEquation *>(T.get())))
                {
                    auto newT = std::unique_ptr<NSEquation>(new NSEquation());
                    newT->CopyFromOldEquation(std::move(T));
                    T = std::move(newT);
                    T->CheckCreate(*Zone);
                }
            }
            AppRes::SolveCenter->TemperatureGroup.Equations.push_back(T.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Normal6.push_back(T.get());
            AppRes::MonitorCenter->Temperature.Residuals.push_back(T.get());
        }
        else
        {
            T = nullptr;
        }
    }
    void ZoneCFDFields::SetParameter_T()
    {
        if (T == nullptr)
            return;
        if (auto *te = dynamic_cast<PossionEquation *>(T.get()))
        {
            te->SetZone_CommonTerm(Material->ThermalConductivity->GetCopy(Zone),
                                   Zone->EnergySource->GetACopy(Zone), PhysicalModel->InitialTemperature->GetCopy(Zone), PhysicalModel->EnergyRelaxFactor);
            if (AppRes::SolveCenter->IsTransient)
            {
                T->SetZone_TransTerm(true, Material->SpecificHeat->GetCopy(Zone), Density);
                AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(T->TransData.get());
            }
            else
            {
                T->SetZone_TransTerm(false, nullptr, nullptr);
            }
            for (auto &t : Zone->BoundThreads)
            {
                if (t->GetIsCoupled())
                {
                    te->SetBound_Coupled(*t);
                    continue;
                }
                switch (t->WallThermalType)
                {
                case WallThermalTypes::FixTemperature:
                    te->SetBoundary_FixValue(t->Temperature->GetCopy(Zone), *t);
                    break;
                case WallThermalTypes::FixHeatFlux:
                    te->SetBoundary_FixFlux(t->HeatFlux->GetCopy(Zone), *t);
                    break;
                case WallThermalTypes::FixhT:
                    te->SetBoundary_FixCoupledhT(t->Coupledh->GetCopy(Zone), t->CoupledT->GetCopy(Zone), *t);
                    break;
                }
            }
        }
        else if (auto tn = dynamic_cast<NSEquation *>(T.get()))
        {
            auto tDiff = Material->ThermalConductivity->GetCopy(Zone); // GammaCommon == null ? Material.ThermalConductivity.GetCopy(Zone) : GammaCommon;
            std::shared_ptr<Value1Base<double>> specificHeat = Material->SpecificHeat->GetCopy(Zone);
            tn->SetZone_CommonTerm(tDiff, Zone->EnergySource->GetACopy(Zone), PhysicalModel->InitialTemperature->GetCopy(Zone), 0.9);
            tn->SetZone_ConvTerm(specificHeat, PhysicalModel->ConvectionScheme, *Velocity);
            if (AppRes::SolveCenter->IsTransient)
            {
                tn->SetZone_TransTerm(true, specificHeat, Density);
                AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(T->TransData.get());
            }
            else
            {
                tn->SetZone_TransTerm(false, nullptr, nullptr);
            }

            for (auto &thread : Zone->BoundThreads)
            {
                if (thread->GetIsCoupled())
                {
                    tn->SetBoundary_Coupled_Wall(*thread);
                    continue;
                }
                switch (thread->BoundaryType)
                {
                case BoundaryTypes::FluidWall:
                    switch (thread->WallThermalType)
                    {
                    case WallThermalTypes::FixTemperature:
                        tn->SetBoundary_fixValue(thread->Temperature->GetCopy(Zone), *thread);
                        break;
                    case WallThermalTypes::FixHeatFlux:
                        if (thread->HeatFlux->IsEqual0())
                            tn->SetBoundary_symmetry(*thread);
                        else
                            throw std::invalid_argument("流体壁面只支持定温度或绝热," + thread->Name);
                        break;
                    default:
                        throw std::invalid_argument("流体壁面只支持定温度或绝热," + thread->Name);
                        break;
                    }
                    break;
                case BoundaryTypes::Symmetry:
                    tn->SetBoundary_symmetry(*thread);
                    break;
                case BoundaryTypes::VelocityInlet:
                case BoundaryTypes::PressureInOut:
                    tn->SetBoundary_flow(thread->Temperature->GetCopy(Zone), *thread);
                    break;
                default:
                    throw std::invalid_argument("未知边界类型");
                    break;
                }
            }
        }
    }

    void ZoneCFDFields::CheckCreate_Vel()
    {
        bool advice = PhysicalModel->PhysicalType == PhysicalTypes::Fluid;
        if (advice)
        {
            if (Velocity == nullptr)
            {
                Velocity = std::unique_ptr<VelocityVector>(new VelocityVector());
                Velocity->CheckCreate(*Zone);
                PCor = std::unique_ptr<PressureCorrectionBasic>(new PressureCorrection());
                PCor->CheckCreate(*Zone);
                P = std::unique_ptr<PressureSIMPLE>(new PressureSIMPLE());
                P->CheckCreate(*Zone);
            }
            AppRes::SolveCenter->SIMPLEGroup.SIMPLEs.push_back(PCor.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Normal7.push_back(Velocity.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Normal6.push_back(P.get());
            AppRes::MonitorCenter->Vel_U.Residuals.push_back(Velocity->U.get());
            AppRes::MonitorCenter->Vel_V.Residuals.push_back(Velocity->V.get());
            AppRes::MonitorCenter->Vel_W.Residuals.push_back(Velocity->W.get());
            AppRes::MonitorCenter->Continuity.Residuals.push_back(Velocity.get());
        }
        else
        {
            Velocity = nullptr;
            PCor = nullptr;
            P = nullptr;
        }
        // CreateFields_TurbBase(advice);
    }
    void ZoneCFDFields::SetParameter_Vel()
    {
        if (Velocity == nullptr)
            return;
        auto UVW_PSource = std::shared_ptr<Value1Base<Vector3d>>(new Value1OppositeFromArray1::Vector(P->Grad.get()));
        ValueListMaker::Vector uvws;
        uvws.AddValueProvider(UVW_PSource);
        if (PhysicalModel->IsGravityEnabled && PhysicalModel->IsEnergyEnabled && PhysicalModel->IsBoussinesqEnabled)
        {
            if (auto *vd = dynamic_cast<Value1Const::Double *>(Density.get()))
            {
                auto value3D1Base = std::shared_ptr<Value1Base<Vector3d>>(
                    new BoussinesqSource(PhysicalModel->ReferenceTemperature, Material->ThermalExpansionCoefficent, vd->Number, PhysicalModel->Gravity, *Zone));
                uvws.AddValueProvider(value3D1Base);
            }
            else
            {
                throw std::invalid_argument("Boussinesq模型要求密度为常数");
            }
        }
        auto vis = Material->Viscosity->GetCopy(Zone);
        std::shared_ptr<Value1Base<double>> UVWgamma = vis; // GammaCommon == null ? vis : GammaCommon;
        Velocity->SetZone_CommonTerm(UVWgamma, vis, uvws.MakeValueList(), PhysicalModel->InitialVelocity->GetCopy(Zone), 0.5);
        Velocity->SetZone_ConvTerm(Density, PhysicalModel->ConvectionScheme);
        Velocity->SetZone_TransTerm(AppRes::SolveCenter->IsTransient, Value1Const::Double1, Density);
        if (AppRes::SolveCenter->IsTransient)
        {
            AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(Velocity->U->TransData.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(Velocity->V->TransData.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(Velocity->W->TransData.get());
            AppRes::SolveCenter->InitializeGroup.Initialization_Transient9.push_back(Velocity->TransVelData.get());
        }

        PCor->SetZone(0.5, PhysicalModel->SIMPLEMethod, Velocity.get(), P.get(), Density);
        P->SetZone(Value1Const::Double0, Velocity.get(), PCor.get(), Density);
        Velocity->SetZone_RhieChow_AfterSetTrans(PCor.get(), P.get());

        for (auto &t : Zone->BoundThreads)
        {
            switch (t->BoundaryType)
            {
            case BoundaryTypes::FluidWall:
                if (t->IsNoSlipingWall)
                {
                    if (t->IsStaticWall)
                    {
                        Velocity->SetBoundary_NoSlipStaticWall(*t);
                    }
                    else
                    {
                        Velocity->SetBoundary_NoSlipMovingWall(t->Velocity->GetCopy(Zone), *t);
                    }
                }
                else
                {
                    Velocity->SetBoundary_SlipWall(*t);
                }
                break;
            case BoundaryTypes::Symmetry:
                Velocity->SetBoundary_SlipWall(*t);
                break;
            case BoundaryTypes::VelocityInlet:
                if (t->IsNormalToBound)
                {
                    Velocity->SetBound_VelocityInlet(t->VelocityMagnitude->GetCopy(Zone), *t);
                }
                else
                {
                    Velocity->SetBound_VelocityInlet(t->Velocity->GetCopy(Zone), *t);
                }
                break;
            case BoundaryTypes::PressureInOut:
                if (t->IsNormalToBound)
                {
                    Velocity->SetBound_PressureInOut(t->Pressure->GetCopy(Zone), *t);
                }
                else
                {
                    Velocity->SetBound_PressureInOut(t->Pressure->GetCopy(Zone), t->Velocity->GetCopy(Zone), *t);
                }
                break;
            default:
                throw std::invalid_argument("未知边界类型");
                break;
            }
        }
        PCor->SetBound_AfterSettingVelocityVector();
        //SetParameter_TurbBase();
    }

}