#pragma once
#include "ConnectWallBase.h"
namespace LxCFD
{
    class ConnectWallTwoSide : public ConnectWallBase
    {
    public:
        std::shared_ptr<Value1Base<double>> I_Gamma;
        std::shared_ptr<Value1Base<double>> Thickness;
        void setConnect(std::shared_ptr<Value1Base<double>> Tau, std::shared_ptr<Value1Base<double>> Thickness, std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix);
        virtual void SetAb_Step1(int taskIndex)override;
        void setAb_TwoSideWall(PairMatrix &ab, int ofid, FvFace &oface, int nfid, FvFace &nface);
        virtual void Update_x_Bound(int taskIndex)override;
    };
}