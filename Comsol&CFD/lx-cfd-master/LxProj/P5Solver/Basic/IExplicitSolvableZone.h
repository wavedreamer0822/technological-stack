#pragma once

namespace LxCFD
{
    class IExplicitSolvableZone
    {
    public:
        virtual void CalByExplicit_Step1(int taskIndex) = 0;
        virtual void CalByExplicit_Step2(int taskIndex) = 0;
    };
}