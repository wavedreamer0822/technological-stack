#pragma once
#include "MGPair.h"
namespace LxCFD
{
    class IAMGSolvableContact
    {
    public:
        virtual void Restrict_ALU(double &out_ALUO, double &out_ALUN, MGPair &mgPair) = 0;
    };
}