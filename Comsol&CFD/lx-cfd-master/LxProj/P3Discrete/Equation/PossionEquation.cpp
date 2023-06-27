#include "PossionEquation.h"

namespace LxCFD
{
    void PossionEquation::BoundaryFixValue::SetFixValue(std::shared_ptr<Value1Base<double>> fixValue)
    {
        FixValue = fixValue;
        BoundxState.SetState(fixValue->IsConstant());
    }
    void PossionEquation::BoundaryFixFlux::SetFixFlux(std::shared_ptr<Value1Base<double>> fixFlux)
    {
        FixFlux = fixFlux;
    }
    //cell的数据中已设置边界的volumn等于边界面的面积
    void PossionEquation::BoundaryFixhT::SetFixhT(std::shared_ptr<Value1Base<double>> fixh, std::shared_ptr<Value1Base<double>> fixT)
    {
        Fixh = fixh;
        FixT = fixT;
    }
    void PossionEquation::SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> gamma, std::shared_ptr<ValueBase<double>> source, std::shared_ptr<Value1Base<double>> iniValue, double relaxFactor)
    {
        clear_eFlags();
        FixValueBounds.clear();
        FixFluxBounds.clear();
        FixhTBounds.clear();
        CoupledBounds.clear();

        Gamma = gamma;
        Source = source;
        IniValue = iniValue;
        RelaxFactor = relaxFactor;
    }
    void PossionEquation::SetBoundary_FixValue(std::shared_ptr<Value1Base<double>> fixValue, FvThread &thread)
    {
        std::unique_ptr<BoundaryFixValue> boundaryFixValue = std::unique_ptr<BoundaryFixValue>(new BoundaryFixValue());
        boundaryFixValue->SetHead(thread);
        boundaryFixValue->SetFixValue(fixValue);

        FixValueBounds.push_back(std::move(boundaryFixValue));
        e_FixValue.push_back(thread.ID);
    }
    void PossionEquation::SetBoundary_FixFlux(std::shared_ptr<Value1Base<double>> fixFlux, FvThread &thread)
    {
        std::unique_ptr<BoundaryFixFlux> boundaryFixFlux = std::unique_ptr<BoundaryFixFlux>(new BoundaryFixFlux());
        boundaryFixFlux->SetHead(thread);
        boundaryFixFlux->SetFixFlux(fixFlux);

        FixFluxBounds.push_back(std::move(boundaryFixFlux));
        e_ALUO0.push_back(thread.ID);
    }
    void PossionEquation::SetBoundary_FixCoupledhT(std::shared_ptr<Value1Base<double>> fixh, std::shared_ptr<Value1Base<double>> fixT, FvThread &thread)
    {
        std::unique_ptr<BoundaryFixhT> boundaryFixhT = std::unique_ptr<BoundaryFixhT>(new BoundaryFixhT());
        boundaryFixhT->SetHead(thread);
        boundaryFixhT->SetFixhT(fixh, fixT);

        FixhTBounds.push_back(std::move(boundaryFixhT));
        e_ALUO0.push_back(thread.ID);
    }

    void PossionEquation::SetBound_Coupled(FvThread &thread)
    {
        auto coupledBound = std::unique_ptr<BoundaryHeadBase>(new BoundaryHeadBase());
        coupledBound->SetHead(thread);

        CoupledBounds.push_back(std::move(coupledBound));
        e_Couple.push_back(thread.ID);
    }

    void PossionEquation::Initialize()
    {
        MultiThreads::RunCalTasks(
            [this](int taskIndex)
            {
                set_x(*IniValue, *InnerIndex, taskIndex);
                Set_x_Bound(taskIndex);
                for (auto &b : FixFluxBounds)
                {
                    set_x(*IniValue, *b->ThreadIndex, taskIndex);
                }
                for (auto &b : FixhTBounds)
                {
                    set_x(*IniValue, *b->ThreadIndex, taskIndex);
                }
                for (auto &b : CoupledBounds)
                {
                    set_x(*IniValue, *b->ThreadIndex, taskIndex);
                }
            });
    }
    void PossionEquation::Set_x_Bound(int taskIndex)
    {
        for (auto &b : FixValueBounds)
        {
            if (b->BoundxState.GetIsNeedToCal(taskIndex))
            {
                set_x(*b->FixValue, *b->ThreadIndex, taskIndex);
            }
        }
    }

    void PossionEquation::SetAb_Step1(int taskIndex)
    {
        setAb_step1_inner(taskIndex);
        for (auto &b : FixValueBounds)
        {
            setAb_step1_bound(*b->ThreadIndex, taskIndex);
        }
        for (auto &b : FixFluxBounds)
        {
            if (b->FixFlux->IsEqual0())
            {
                setBound_flux0(*b->ThreadIndex, taskIndex);
            }
            else
            {
                setBound_flux(*b->ThreadIndex, b->FixFlux.get(), taskIndex);
            }
        }
        for (auto &b : FixhTBounds)
        {
            setBound_fixhFixT(*b->ThreadIndex, *b->Fixh, *b->FixT, taskIndex);
        }
    }
    void PossionEquation::SetAb_Step2(int taskIndex)
    {
        if (auto *source1 = dynamic_cast<Value1Base<double> *>(Source.get()))
        {
            setAb_step2(*source1, taskIndex);
        }
        else if (auto *source2 = dynamic_cast<Value2Base<double> *>(Source.get()))
        {
            setAb_step2(*source2, taskIndex);
        }
        else
        {
            throw std::invalid_argument("未知的数据类型");
        }
    }
    void PossionEquation::Update_x_Bound(int taskIndex)
    {
        for (auto &b : FixFluxBounds)
        {
            if (b->FixFlux->IsEqual0())
            {
                updateBound_grad0(*b->ThreadIndex, taskIndex);
            }
            else
            {
                updateBound_flux(*b->ThreadIndex, taskIndex);
            }
        }
        for (auto &b : FixhTBounds)
        {
            updateBound_fixhFixT(*b->ThreadIndex, taskIndex);
        }
    }

}