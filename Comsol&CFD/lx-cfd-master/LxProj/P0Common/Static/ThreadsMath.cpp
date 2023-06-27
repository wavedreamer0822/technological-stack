#include "ThreadsMath.h"

namespace LxCFD
{
    KahanSum ThreadsMath::_Sum1;
    KahanSum ThreadsMath::_Sum2;
    KahanSum ThreadsMath::_Sum3;
    void ThreadsMath::AddToSum(double toSum1)
    {
        std::unique_lock lck(MultiThreads::GlobalMutex);
        _Sum1.Add(toSum1);
    }
    void ThreadsMath::AddToSum(double toSum1, double toSum2)
    {
        std::unique_lock lck(MultiThreads::GlobalMutex);
        _Sum1.Add(toSum1);
        _Sum2.Add(toSum2);
    }
    void ThreadsMath::AddToSum(double toSum1, double toSum2, double toSum3)
    {
        std::unique_lock lck(MultiThreads::GlobalMutex);
        _Sum1.Add(toSum1);
        _Sum2.Add(toSum2);
        _Sum3.Add(toSum3);
    }
    void ThreadsMath::GetSum(double &out_Sum1, double &out_Sum2, double &out_Sum3)
    {
        out_Sum1 = _Sum1.GetSum();
        out_Sum2 = _Sum2.GetSum();
        out_Sum3 = _Sum3.GetSum();
    }
    void ThreadsMath::AddTo(std::atomic<int> &target, int addend)
    {
        target += addend;
    }
    void ThreadsMath::AddTo(std::atomic<double> &target, double addend)
    {
        double initialValue, computedValue;
        do
        {
            initialValue = target;
            if (std::isnan(initialValue))
                return; //NaN ！= NaN,所以排除
            computedValue = initialValue + addend;
        } while (!target.compare_exchange_weak(initialValue, computedValue));
    }
    void ThreadsMath::KeepMax(std::atomic<double> &target, double potentialMax)
    {
        double initialValue;
        do
        {
            initialValue = target;
            if (std::isnan(initialValue))
                return; //NaN ！= NaN,所以排除
            if (potentialMax <= initialValue)
                return;
        } while (!target.compare_exchange_weak(initialValue, potentialMax));
    }
    void ThreadsMath::KeepMin(std::atomic<double> &target, double potentialMin)
    {
        double initialValue;
        do
        {
            initialValue = target;
            if (std::isnan(initialValue))
                return; //NaN ！= NaN,所以排除
            if (potentialMin >= initialValue)
                return;
        } while (!target.compare_exchange_weak(initialValue, potentialMin));
    }

}
