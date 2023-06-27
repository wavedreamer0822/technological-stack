#pragma once
#include "TransientTimeBase.h"
namespace LxCFD
{
    class TransientTimeFixed : public TransientTimeBase
    {
    public:
        double FixInterval=1;
        virtual void Initialize() override;
        virtual void MoveNextTimeStep() override;
        virtual std::unique_ptr<TransientTimeBase> GetCopy() override;

    protected:
        void setTime();
    };
}