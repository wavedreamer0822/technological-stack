#pragma once
#include "EquationBase.h"

namespace LxCFD
{
    class PossionEquationBase : public EquationBase
    {
    public:
        std::shared_ptr<Value1Base<double>> Gamma;

    protected:
        void setAb_step1_inner(int taskIndex);
        void setAb_step1_bound(IndexNumber &indexNumber, int taskIndex);
        void setBound_flux0(IndexNumber &indexNumber, int taskIndex);
        void setBound_flux(IndexNumber &indexNumber, ValueBase<double> *flux, int taskIndex);
        void updateBound_flux(IndexNumber &indexNumber, int taskIndex);
        void setBound_fixhFixT(IndexNumber &indexNumber, Value1Base<double> &fixh, Value1Base<double> &fixT, int taskIndex);
        void updateBound_fixhFixT(IndexNumber &indexNumber, int taskIndex);
        void setAb_step2(Value2Base<double> &source2, int taskIndex);
        void setAb_step2(Value1Base<double> &source1, int taskIndex);
    };
}