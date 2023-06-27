#pragma once
#include "ConnectWallBase.h"
namespace LxCFD
{
    class ConnectWallOneSide : public ConnectWallBase
    {
    public:
        void setConnect(std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix);
        virtual void SetAb_Step1(int taskIndex) override;
        void setAb_oneSideWall(PairMatrix &ab, int ofid, FvFace &oface, int nfid, FvFace &nface);
        virtual void Update_x_Bound(int taskIndex) override;
    };
}