#include "ConnectWallBase.h"

namespace LxCFD
{
    void ConnectWallBase::setArray_2(std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix)
    {
        SetArray(*OMatrix, *NMatrix);
        O_Gamma = getGamma(O_Matrix);
        N_Gamma = getGamma(N_Matrix);

        this->S = S;
    }
    std::shared_ptr<Value1Base<double>> ConnectWallBase::getGamma(EquationBase *m)
    {
        if (auto *possion = dynamic_cast<PossionEquationBase *>(m))
        {
            return possion->Gamma;
        }
        // else if (m is NSEquationBase ns)
        // {
        //     return ns.Gamma;
        // }
        else
        {
            throw std::invalid_argument("无法获取公式中Gamma值");
        }
    }
    void ConnectWallBase::setAb_ONALU(PairMatrix &ab, int ofid, int nfid)
    {
        O_ALUN->at(ofid) = -ab.a11;
        O_ALUO->at(ofid) = 1;
        O_bFaceCommon->at(ofid) = ab.b1;
        N_ALUN->at(nfid) = -ab.a44;
        N_ALUO->at(nfid) = 1;
        N_bFaceCommon->at(nfid) = ab.b4;
    }
}