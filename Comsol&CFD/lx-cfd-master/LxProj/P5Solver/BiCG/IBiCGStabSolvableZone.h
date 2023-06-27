#pragma once

namespace LxCFD
{
    class IBiCGStabSolvableZone
    {
    public:
        virtual void Initialize_Step1_r0rp1rho(int taskIndex) = 0;
        virtual void Cal_rhoPart1(int taskIndex) = 0;
        virtual void Cal_pArray(int taskIndex) = 0;
        virtual void Cal_yArray(int taskIndex) = 0;
        virtual void Cal_vArray_alpha1(int taskIndex) = 0;
        virtual void Cal_sArray(int taskIndex) = 0;
        virtual void Cal_zArray(int taskIndex) = 0;
        virtual void Cal_tArray_omega1(int taskIndex) = 0;
        virtual void Cal_xArray(int taskIndex) = 0;
        virtual void Cal_rArray(int taskIndex) = 0;
    };
}