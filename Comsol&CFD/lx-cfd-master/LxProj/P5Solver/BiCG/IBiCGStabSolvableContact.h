#pragma once

namespace LxCFD
{
    class IBiCGStabSolvableContact
    {
    public:
        virtual void Copy_yArray(int taskIndex) = 0;
        virtual void Copy_zArray(int taskIndex) = 0;
    };
}