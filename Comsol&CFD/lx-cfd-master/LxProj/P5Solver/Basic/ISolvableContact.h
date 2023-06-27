#pragma once
#include "IBiCGStabSolvableContact.h"
namespace LxCFD
{
    class ISolvableContact : public IBiCGStabSolvableContact
    {
    public:
        virtual void Copy_xArray(int taskIndex) = 0;
        virtual void Copy_xCommonArray(int taskIndex) = 0;
    };
}