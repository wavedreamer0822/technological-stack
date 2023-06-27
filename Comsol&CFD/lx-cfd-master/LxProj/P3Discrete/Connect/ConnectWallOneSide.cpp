#include "ConnectWallOneSide.h"

namespace LxCFD
{
    void ConnectWallOneSide::setConnect(std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix)
    {
        setArray_2(S, OMatrix, NMatrix);
    }
    void ConnectWallOneSide::SetAb_Step1(int taskIndex)
    {
        if (auto *s1 = dynamic_cast<Value1Base<double> *>(S.get()))
        {
            if (s1->IsEqual0())
            {
                int i1, endp1;
                InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
                for (; i1 < endp1; ++i1)
                {
                    PairMatrix &ab = ADLUb->at(i1);
                    ab.b2 = 0;
                    ab.a22 = 0;

                    int ofid = i1 + deltaOFaceId;
                    int nfid = i1 + deltaNFaceId;
                    setAb_oneSideWall(ab, ofid, O_Faces->at(ofid), nfid, N_Faces->at(nfid));
                }
            }
            else
            {
                int i1, endp1;
                InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
                for (; i1 < endp1; ++i1)
                {
                    PairMatrix &ab = ADLUb->at(i1);
                    int ofid = i1 + deltaOFaceId;
                    FvFace &oface = O_Faces->at(ofid);
                    ab.b2 = s1->GetFaceValue(ofid) * oface.Area;
                    ab.a22 = 0;

                    int nfid = i1 + deltaNFaceId;
                    setAb_oneSideWall(ab, ofid, oface, nfid, N_Faces->at(nfid));
                }
            }
        }
        else if (auto *s2 = dynamic_cast<Value2Base<double> *>(S.get()))
        {
            int i1, endp1;
            InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
            for (; i1 < endp1; ++i1)
            {
                PairMatrix &ab = ADLUb->at(i1);
                int ofid = i1 + deltaOFaceId;
                FvFace &oface = O_Faces->at(ofid);
                double sou_ad, sou_b;
                s2->GetFaceValue(sou_ad, sou_b, ofid);
                ab.b2 = sou_b * oface.Area;
                ab.a22 = -sou_ad * oface.Area;

                int nfid = i1 + deltaNFaceId;
                setAb_oneSideWall(ab, ofid, oface, nfid, N_Faces->at(nfid));
            }
        }
        else
        {
            throw std::invalid_argument("接触面源项无法识别");
        }
    }
    void ConnectWallOneSide::setAb_oneSideWall(PairMatrix &ab, int ofid, FvFace &oface, int nfid, FvFace &nface)
    {
        double ogamma = O_Gamma->GetFaceValue(ofid);
        double ogg = ogamma * oface.gDiff;
        double ocor_a, ocor_b;
        double ofacecor = ogamma * oface.CalNonOrthogonalityCorrection_bound(ocor_a, ocor_b, *O_grad, *O_x, *O_Cells);
        ocor_a *= ogamma;
        ocor_b *= ogamma;

        double ngamma = N_Gamma->GetFaceValue(nfid);
        double ngg = ngamma * nface.gDiff;
        double ncor_a, ncor_b;
        double nfacecor = ngamma * nface.CalNonOrthogonalityCorrection_bound(ncor_a, ncor_b, *N_grad, *N_x, *N_Cells);
        ncor_a *= ngamma;
        ncor_b *= ngamma;

        ab.a11 = ogg;
        ab.a12 = -ogg;
        ab.b1 = ofacecor;
        ab.a44 = ngg;
        ab.a43 = -ngg;
        ab.b4 = nfacecor;
        ab.a22 += ogg + ngg + ocor_a + ncor_a; //一次成型
        ab.a21 = -ogg - ocor_a;
        ab.a24 = -ngg - ncor_a;
        ab.b2 += -(ocor_b + ncor_b);
        //第三行均没有赋值，也没有初始化,直接按等于第二行赋值
        ab.a31 = ab.a21;
        ab.a33 = ab.a22;
        ab.a34 = ab.a24;
        ab.b3 = ab.b2;
        ab.Eliminate_a12a43();
        setAb_ONALU(ab, ofid, nfid);
    }
    void ConnectWallOneSide::Update_x_Bound(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvPair &pair = Pairs->at(i1);
            PairMatrix &ab = ADLUb->at(i1);
            double &x1 = O_x->at(pair.O_InnCell);
            double &x4 = N_x->at(pair.N_InnCell);
            O_x->at(pair.O_Cell) = N_x->at(pair.N_Cell) = (ab.b2 - ab.a21 * x1 - ab.a24 * x4) / ab.a22;
        }
    }
}