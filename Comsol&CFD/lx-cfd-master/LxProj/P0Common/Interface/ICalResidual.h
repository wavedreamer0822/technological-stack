#pragma once
namespace LxCFD
{
    class ICalResidual
    {
    public:
        virtual void CalResidual(int taskIndex) = 0;
        virtual void GetResidual_Reset(double &out_maxRc, double &out_maxacPhic) = 0;
    };
}
