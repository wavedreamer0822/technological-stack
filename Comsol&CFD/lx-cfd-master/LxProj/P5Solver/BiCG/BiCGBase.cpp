#include "BiCGBase.h"
#include "ThreadsMath.h"

namespace LxCFD
{
    double BiCGBase::rho = 0;
    double BiCGBase::alpha = 0;
    double BiCGBase::omega = 0;
    double BiCGBase::beta = 0;
    bool BiCGBase::GetIsNeededToBreak(double d)
    {
        return d < 1e-20;
    }
    bool BiCGBase::Initialize_Step2()
    {
        rho = 1;
        alpha = 1;
        omega = 1;
        return Cal_rhobeta();
    }
    bool BiCGBase::Cal_rhobeta() //1.2
    {
        double rho_new, sum2, sum3;
        ThreadsMath::GetSum(rho_new, sum2, sum3);
        if (GetIsNeededToBreak(rho_new))
            return true;
        if (GetIsNeededToBreak(omega))
            return true;
        beta = (rho_new / rho) * (alpha / omega);
        rho = rho_new;
        return false;
    }
    bool BiCGBase::Cal_alpha() //5.2
    {
        double r0v, sum2, sum3;
        ThreadsMath::GetSum(r0v, sum2, sum3);
        if (GetIsNeededToBreak(r0v))
            return true;
        alpha = rho / r0v;
        return false;
    }
    bool BiCGBase::Cal_omega() //9.2
    {
        double ts, tt, sum3;
        ThreadsMath::GetSum(ts, tt, sum3);
        if (GetIsNeededToBreak(tt))
            return true;
        omega = ts / tt;
        return false;
    }
}