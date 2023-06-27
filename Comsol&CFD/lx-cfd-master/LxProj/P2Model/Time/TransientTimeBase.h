#pragma once
#include <memory>
#include "TransientDataBase.h"

namespace LxCFD
{
    class TransientTimeBase
    {
    public:
        double ResultTime=0; //对于显示格式，Result的时间在离散方程的下一个，对于隐式是一样的，ResultTime即为t时间，对于的时间间隔为delta_t

        bool IsImplicit = true;
        bool IsSecondOrder = true;

        double EquationTime=0; //离散方程对应的时间，在每次调用isContinue时，要准备好下一次计算的equationTime
        double dt=0;
        double dto=0;
        double dtoo=0;

        virtual void Initialize() = 0;
        virtual void MoveNextTimeStep() = 0;
        virtual std::unique_ptr<TransientTimeBase> GetCopy() = 0;
        void SetTransientFactor();
        void GetFactor_1stOrderExplicit(double &out_beforePhi);
        void GetFactor_2ndOrderExplicit(double &out_beforePhi, double &out_beforePhiOld, double &out_beforePhiOld2);
        void GetFactor_1stOrderImplicit(double &out_beforePhi);
        void GetFactor_2ndOrderImplicit(double &out_beforePhi, double &out_beforePhiOld, double &out_beforePhiOld2);
    };
}