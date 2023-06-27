#pragma once

namespace LxCFD
{
    class IJacobiSolvableZone
    {
    public:
        virtual void CalByJacobi_Step1(int taskIndex) = 0;
        virtual void CalByJacobi_Step2(int taskIndex) = 0;
    };
}