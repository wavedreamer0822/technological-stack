#pragma once

namespace LxCFD
{
    class BiCGBase
    {
    public:
        static double rho;
        static double alpha;
        static double omega;
        static double beta;
        static bool GetIsNeededToBreak(double d);
        static bool Initialize_Step2();
        static bool Cal_rhobeta();
        static bool Cal_alpha();
        static bool Cal_omega();
    };
}