#include "FvFace.h"
#include <cmath>
#include "LxConsole.h"
#include "FvCell.h"
namespace LxCFD
{
    FvFace::FvFace() {}
    void FvFace::Set(ShortArray::Deep &store, const ShortArray::Shallow &nodes, int c0, int c1, bool isRightHand)
    {
        OSideCell = c0;
        NSideCell = c1;
        NodeIDs = store.Create(nodes);
        if (!isRightHand)
        {
            NodeIDs.Reverse();
        }
    }
    void FvFace::CalGeometryInFace(std::vector<Vector3d> &points)
    {
        Center = Vector3d();
        Normal = Vector3d();
        double areaWeightSum = 0; //如果这几个三角面不在一个平面，不至于出错
        if (NodeIDs.GetLengh() < 3)
        {
            LxConsole::Error("存在面的边数小于3");
            return;
        }

        for (int i1 = 2; i1 < NodeIDs.GetLengh(); ++i1)
        {
            Vector3d CenterMultiply3;
            Vector3d NormalMultiply2;
            CalTriangleGeometry(CenterMultiply3, NormalMultiply2,
                                points.at(NodeIDs.at(0)),
                                points.at(NodeIDs.at(i1 - 1)),
                                points.at(NodeIDs.at(i1)));
            double areaWeight = NormalMultiply2.CalLength();
            areaWeightSum += areaWeight;
            Center += (areaWeight * CenterMultiply3);
            Normal += (NormalMultiply2);
        }
        Normal *= (0.5);
        Area = Normal.CalLength();
        Center *= (1 / (3 * areaWeightSum));
        if (Area == 0)
        {
            LxConsole::Error("存在面积为0的面");
        }
    }

    void FvFace::CalGeometryAcrossFace_inner(std::vector<FvCell> &cells)
    {
        calO2N(cells);
        if (OToNLength == 0)
        {
            gOwner = 0.5;
            return;
        } //上面已提示过了
        Vector3d ownerToFace = Center - cells.at(OSideCell).Center;
        gOwner = Vector3d::DotProduct(ownerToFace, OToN) / OToN.CalLengthSquared();
        if (gOwner > 1)
        {
            gOwner = 1;
        }
        else if (gOwner < 0)
        {
            gOwner = 0;
        }
    }

    void FvFace::CalGeometryAcrossFace_bound(std::vector<FvCell> &cells)
    {
        calO2N(cells);
        gOwner = 1;
    }
    Vector3d FvFace::CalONGradient_DistanceWeighted(std::vector<double> &phi) //求解Grad 梯度时使用
    {
        double deltaPhiWithDistace = (phi.at(NSideCell) - phi.at(OSideCell)) / OToNLength;
        return deltaPhiWithDistace * OToN;
    }
    ONPair FvFace::GetONCellID()
    {
        return ONPair(OSideCell, NSideCell);
    }
    double FvFace::CalAverage(std::vector<double> &phi)
    {
        return phi.at(OSideCell) * (1 - gOwner) + phi.at(NSideCell) * gOwner;
    }
    Vector3d FvFace::CalAverage(std::vector<Vector3d> &gradPhi)
    {
        return (1 - gOwner) * gradPhi.at(OSideCell) + gOwner * gradPhi.at(NSideCell);
    }
    Vector3d FvFace::CalCFCorrectedGradient_inner(std::vector<Vector3d> &gradPhi, std::vector<double> &phi)
    {
        Vector3d aveGrad = CalAverage(gradPhi);
        Vector3d cor = calCFCorrectPart(aveGrad, phi);
        return aveGrad + cor;
    }
    Vector3d FvFace::CalCFCorrectedGradient_bound(std::vector<Vector3d> &gradPhi, std::vector<double> &phi)
    {
        Vector3d aveGrad = gradPhi.at(OSideCell);
        Vector3d cor = calCFCorrectPart(aveGrad, phi);
        return aveGrad + cor;
    }
    Vector3d FvFace::CalCFGradCorrection_inner(std::vector<Vector3d> &gradPhi, std::vector<double> &phi)
    {
        Vector3d aveGrad = CalAverage(gradPhi);
        return calCFCorrectPart(aveGrad, phi);
    }

    Vector3d FvFace::CalCFGradCorrection_bound(std::vector<Vector3d> &gradPhi, std::vector<double> &phi)
    {
        Vector3d aveGrad = gradPhi.at(OSideCell);
        return calCFCorrectPart(aveGrad, phi);
    }
    double FvFace::CalNonOrthogonalityCorrection_inner(std::vector<Vector3d> &gradPhi, std::vector<double> &phi) //公式整合
    {
        return calNonOrthogonalityCorrection(CalAverage(gradPhi), phi);
    }

    double FvFace::CalNonOrthogonalityCorrection_bound(std::vector<Vector3d> &gradPhi, std::vector<double> &phi)
    {
        return calNonOrthogonalityCorrection(gradPhi.at(OSideCell), phi);
    }

    double FvFace::CalNonOrthogonalityCorrection_bound(double &out_a, double &out_b, std::vector<Vector3d> &gradPhi, std::vector<double> &phi, std::vector<FvCell> &cells) //只写了匹配minCorrection的//虽然不是minCorrect也可能能用，但应该重新推导公式，进行源项线性化
    {
        out_a = (pow(Area, 2) - pow(GetgT() * OToNLength, 2)) / cells.at(OSideCell).Volumn;
        double cor = calNonOrthogonalityCorrection(gradPhi.at(OSideCell), phi);
        out_b = cor - out_a * (phi.at(NSideCell) - phi.at(OSideCell));
        return cor;
    }
    //private
    void FvFace::CalTriangleGeometry(Vector3d &out_CenterMultiply3, Vector3d &out_AreaMultiply2, const Vector3d &p0, const Vector3d &p1, const Vector3d &p2)
    {
        Vector3d v01 = p1 - p0;
        Vector3d v12 = p2 - p1;
        out_AreaMultiply2 = Vector3d::CrossProduct(v01, v12);
        out_CenterMultiply3 = Vector3d(p0.X + p1.X + p2.X, p0.Y + p1.Y + p2.Y, p0.Z + p1.Z + p2.Z);
    }

    void FvFace::calO2N(std::vector<FvCell> &cells)
    {
        OToN = cells.at(NSideCell).Center - cells.at(OSideCell).Center;
        OToNLength = OToN.CalLength();
        double normalDotOToN = Vector3d::DotProduct(Normal, OToN);
        if (normalDotOToN < 0)
        {
            LxConsole::Error("面的Owner关系与面的朝向不一致，极可能是网格导入错误");
        }
        if (OToNLength == 0)
        {
            LxConsole::Error("网格中心重叠，计算会出现错误！");
        }
        //---------------------修改点1------------------------------------
#if FaceCorOption == 0
        //!!!!!!!!!!!以下为minCorrection
        this->gDiff = normalDotOToN / pow(OToNLength, 2);
#else
        //!!!!!!!!!!!以下为overCorrection修改点1
        this->gDiff = pow(Area, 2) / normalDotOToN;
        this->_gT = normalDotOToN / pow(OToNLength, 2);
#endif
    }
    Vector3d FvFace::calCFCorrectPart(const Vector3d &aveGrad, std::vector<double> &phi) //求解C F 网格值修正部分
    {
        return (phi.at(NSideCell) - phi.at(OSideCell) - Vector3d::DotProduct(aveGrad, OToN)) / pow(OToNLength, 2) * OToN;
    }
    double FvFace::calNonOrthogonalityCorrection(const Vector3d &aveGrad, std::vector<double> &phi)
    {
        //----------------------------修改点2-----------------------------------
#if FaceCorOption == 0
        //!!!!!!!!以下为minCorrection
        return Vector3d::DotProduct(aveGrad, Normal - gDiff * OToN);
#else
        //!!!!!!!!!以下为overCorrection
        return Vector3d.DotProduct(aveGrad, Normal - _gT * OToN) + (phi->at(NSideCell) - phi->at(OSideCell)) * (_gT - gDiff);
#endif
    }
}

// FvFace::FvFace(const std::vector<int> &nodes, int c0, int c1, bool isRightHand) : NodeIDs(nodes), OSideCell(c0), NSideCell(c1)
// {
//     if (!isRightHand)
//     {
//         NodeIDs.Reverse();
//     }
// }