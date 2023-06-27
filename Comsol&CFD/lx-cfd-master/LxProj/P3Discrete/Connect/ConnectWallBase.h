#pragma once
#include <exception>
#include "ConnectBase.h"
#include "PossionEquationBase.h"
namespace LxCFD
{
    class ConnectWallBase : public ConnectBase
    {

    protected:
        std::shared_ptr<Value1Base<double>> O_Gamma;
        std::shared_ptr<Value1Base<double>> N_Gamma;

        std::shared_ptr<ValueBase<double>> S; //√Ê‘¥£¨£°£°£°£°

        void setArray_2(std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix);
        std::shared_ptr<Value1Base<double>> getGamma(EquationBase *m);
        void setAb_ONALU(PairMatrix &ab, int ofid, int nfid);
    };
}