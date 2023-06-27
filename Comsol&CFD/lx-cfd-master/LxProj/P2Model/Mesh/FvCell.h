#pragma once
#include <vector>
#include "FvFace.h"
#include "ShortArray.h"
#include "Vector3d.h"
#include "MatrixToCalGrad_LeastSquare_LengthWeighted.h"

namespace LxCFD
{
    struct FvCell
    {
    public:
        //拓扑关系
        ShortArray::Shallow OFaces;
        ShortArray::Shallow NFaces;
        //几何信息，内部
        Vector3d Center; //对于边界，等于边界面的中心
        double Volumn;   //对于边界，等于边界面的面积，

    private:
        MatrixToCalGrad_LeastSquare_LengthWeighted MatrixToCalGrad;

    public:
        void CalGeometry_inner(std::vector<FvFace> &faces);
        void CalGeometry_bound(std::vector<FvFace> &faces);
        void CalMatrix_LeastSquare(std::vector<FvFace> &faces);
        Vector3d CalGradient_LeastSquare(std::vector<FvFace> &faces, std::vector<double> &phi);
        double CalIfOwnerAddElseMunus(std::vector<double> &faceDataArray);
        double CalAllAdd(std::vector<double> &faceDataArray);
        double CalAllAdd(std::vector<double> &Oface, std::vector<double> &Nface);
    };
}