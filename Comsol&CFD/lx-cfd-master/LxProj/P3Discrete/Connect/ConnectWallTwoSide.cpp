#include "ConnectWallTwoSide.h"

namespace LxCFD
{
    void ConnectWallTwoSide::setConnect(std::shared_ptr<Value1Base<double>> Tau, std::shared_ptr<Value1Base<double>> Thickness, std::shared_ptr<ValueBase<double>> S, EquationBase *OMatrix, EquationBase *NMatrix)
    {
        setArray_2(S, OMatrix, NMatrix);

        this->I_Gamma = Tau;
        this->Thickness = Thickness;
    }
    void ConnectWallTwoSide::SetAb_Step1(int taskIndex)
    {
        if (auto *s1 = dynamic_cast<Value1Base<double> *>(S.get()))
        {
            if (s1->IsEqual0()) //s1 is Value1Const s1c && s1c.number == 0
            {
                int i1, endp1;
                InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
                for (; i1 < endp1; ++i1)
                {
                    PairMatrix &ab = ADLUb->at(i1);
                    ab.b2 = ab.b3 = 0;
                    ab.a22 = ab.a33 = 0;

                    int ofid = i1 + deltaOFaceId;
                    int nfid = i1 + deltaNFaceId;
                    setAb_TwoSideWall(ab, ofid, O_Faces->at(ofid), nfid, N_Faces->at(nfid));
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
                    double s = s1->GetFaceValue(ofid) * oface.Area / 2;
                    ab.b2 = ab.b3 = s;
                    ab.a22 = ab.a33 = 0;

                    int nfid = i1 + deltaNFaceId;
                    setAb_TwoSideWall(ab, ofid, oface, nfid, N_Faces->at(nfid));
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
                double halfArea = oface.Area / 2;
                double sou_ad, sou_b;
                s2->GetFaceValue(sou_ad, sou_b, ofid);
                ab.b2 = ab.b3 = sou_b * halfArea;
                ab.a22 = ab.a33 = -sou_ad * halfArea;

                int nfid = i1 + deltaNFaceId;
                setAb_TwoSideWall(ab, ofid, oface, nfid, N_Faces->at(nfid));
            }
        }
        else
        {
            throw std::invalid_argument("接触面源项无法识别");
        }
    }
    void ConnectWallTwoSide::setAb_TwoSideWall(PairMatrix &ab, int ofid, FvFace &oface, int nfid, FvFace &nface)
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

        double igg = I_Gamma->GetFaceValue(ofid) * oface.Area / Thickness->GetFaceValue(ofid);

        ab.a11 = ogg;
        ab.a12 = -ogg;
        ab.b1 = ofacecor;
        ab.a44 = ngg;
        ab.a43 = -ngg;
        ab.b4 = nfacecor;
        ab.a23 = ab.a32 = -igg;
        ab.a22 += ogg + igg + ocor_a;
        ab.a21 = -ogg - ocor_a;
        ab.b2 += -ocor_b;
        ab.a33 += ngg + igg + ncor_a;
        ab.a34 = -ngg - ncor_a;
        ab.b3 += -ncor_b;
        ab.Eliminate_a23a32();
        ab.Eliminate_a12a43();
        setAb_ONALU(ab, ofid, nfid);
    }
    void ConnectWallTwoSide::Update_x_Bound(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvPair &pair = Pairs->at(i1);
            PairMatrix &ab = ADLUb->at(i1);
            double &x1 = O_x->at(pair.O_InnCell);
            double &x4 = N_x->at(pair.N_InnCell);
            O_x->at(pair.O_Cell) = (ab.b2 - ab.a21 * x1 - ab.a24 * x4) / ab.a22;
            N_x->at(pair.N_Cell) = (ab.b3 - ab.a31 * x1 - ab.a34 * x4) / ab.a33;
        }
    }
}