#pragma once
#include <atomic>
#include "MultiThreads.h"
#include "ScalarHeadBase.h"

namespace LxCFD
{
    class ScalarBase : public ScalarHeadBase
    {
    public:
        std::shared_ptr<std::vector<double>> x; //³¡
        std::shared_ptr<std::vector<Vector3d>> Grad;
        std::shared_ptr<Value1Base<double>> IniValue;
        virtual void CheckCreate(FvZone &zone) override;
        void CalGradient(int taskIndex);
        void CalBoundValue_grad0(FvFace &face);

    protected:
        void set_x(Value1Base<double> &xValue, IndexNumber &indexNumber, int taskIndex);
        void updateBound_grad0(IndexNumber &indexNumber, int taskIndex);
        void predict_bound_byCGrad(IndexNumber &indexNumber, int taskIndex);

    public:
        bool IsEnableLimit = false;
        double MinLim;
        double MaxLim;
        bool IsLimMin;
        bool IsLimMax;
        static std::atomic<int> UnnormalCount;
        static std::atomic<int> ExceedMaxCount;
        static std::atomic<int> ExceedMinCount;
        void SetLimitRule(bool isEnable, bool isLimMin, double minLim, bool isLimMax, double maxLim);
        void Limit_x();

    protected:
        void limitNaN(int taskIndex);
        void limitMax(int taskIndex);
        void limitMin(int taskIndex);
        void limitMinMax(int taskIndex);
    };
}