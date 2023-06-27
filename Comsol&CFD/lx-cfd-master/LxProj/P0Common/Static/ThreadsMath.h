#pragma once
#include <thread>
#include <atomic>
#include <cmath>
#include "MultiThreads.h"
#include "KahanSum.h"

namespace LxCFD
{
    class ThreadsMath
    {
    private:
        static KahanSum _Sum1;
        static KahanSum _Sum2;
        static KahanSum _Sum3;

    public:
        static void AddToSum(double toSum1);
        static void AddToSum(double toSum1, double toSum2);
        static void AddToSum(double toSum1, double toSum2, double toSum3);
        static void GetSum(double &out_Sum1, double &out_Sum2, double &out_Sum3);

        static void AddTo(std::atomic<int> &target, int addend);
        static void AddTo(std::atomic<double> &target, double addend);
        static void KeepMax(std::atomic<double> &target, double potentialMax);
        static void KeepMin(std::atomic<double> &target, double potentialMin);
    };
}