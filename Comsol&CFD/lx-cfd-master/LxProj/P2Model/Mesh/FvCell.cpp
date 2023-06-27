#include "FvCell.h"
#include "LxConsole.h"

namespace LxCFD
{
    void FvCell::CalGeometry_inner(std::vector<FvFace> &faces)
    {
        Vector3d Center; //先重置为0，后期全部改为vector3d类型
        Volumn = 0;      //先重置为0
        for (auto &ofid : OFaces)
        {
            FvFace &face = faces.at(ofid);
            double volWeight = Vector3d::DotProduct(face.Center, face.Normal);
            Center += (volWeight * face.Center);
            Volumn += volWeight;
        }
        for (auto &nfid : NFaces)
        {
            FvFace &face = faces.at(nfid);
            double volWeight = -Vector3d::DotProduct(face.Center, face.Normal); //多一负号
            Center += (volWeight * face.Center);
            Volumn += volWeight;
        }
        if (Volumn <= 0)
        {
            LxConsole::Error("发现体积小于等于0的网格，会导致计算出错");
        }
        else
        {
            Center *= (0.75 / Volumn);
            this->Center = Center;
            Volumn /= 3.0;
        }
    }

    void FvCell::CalGeometry_bound(std::vector<FvFace> &faces)
    {
        FvFace &face = faces.at(NFaces[0]);
        Center = face.Center;
        Volumn = face.Area;
    }

    void FvCell::CalMatrix_LeastSquare(std::vector<FvFace> &faces)
    {
        MatrixToCalGrad = MatrixToCalGrad_LeastSquare_LengthWeighted();
        for (auto &ofid : OFaces)
        {
            MatrixToCalGrad.AddVector_FromThisToAdjacent(faces.at(ofid).OToN);
        }
        for (auto &nfid : NFaces)
        {
            MatrixToCalGrad.AddVector_FromThisToAdjacent(-faces.at(nfid).OToN);
        }
        MatrixToCalGrad.Inverse();
    }

    Vector3d FvCell::CalGradient_LeastSquare(std::vector<FvFace> &faces, std::vector<double> &phi)
    {
        Vector3d v3d;
        for (auto &ofid : OFaces)
        {
            v3d += (faces.at(ofid).CalONGradient_DistanceWeighted(phi));
        }
        for (auto &nfid : NFaces)
        {
            v3d += (faces.at(nfid).CalONGradient_DistanceWeighted(phi));
        }
        return MatrixToCalGrad.CalGradPhi(v3d);
    }

    double FvCell::CalIfOwnerAddElseMunus(std::vector<double> &faceDataArray)
    {
        double result = 0;
        for (auto &ofid : OFaces)
        {
            result += faceDataArray.at(ofid);
        }
        for (auto &nfid : NFaces)
        {
            result -= faceDataArray.at(nfid);
        }
        return result;
    }

    double FvCell::CalAllAdd(std::vector<double> &faceDataArray)
    {
        double result = 0;
        for (auto &ofid : OFaces)
        {
            result += faceDataArray.at(ofid);
        }
        for (auto &nfid : NFaces)
        {
            result += faceDataArray.at(nfid);
        }
        return result;
    }

    double FvCell::CalAllAdd(std::vector<double> &Oface, std::vector<double> &Nface)
    {
        double result = 0;
        for (auto &ofid : OFaces)
        {
            result += Oface.at(ofid);
        }
        for (auto &nfid : NFaces)
        {
            result += Nface.at(nfid);
        }
        return result;
    }

}