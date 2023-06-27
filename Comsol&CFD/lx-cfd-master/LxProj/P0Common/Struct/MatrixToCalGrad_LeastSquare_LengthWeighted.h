#pragma once
#include "Vector3d.h"
#include "MatrixR3C3.h"

namespace LxCFD
{
    struct MatrixToCalGrad_LeastSquare_LengthWeighted
    {
    public:
        double a11 = 0;
        // double a12;
        // double a13;
        double a21 = 0;
        double a22 = 0;
        // double a23;
        double a31 = 0;
        double a32 = 0;
        double a33 = 0;

        void AddVector_FromThisToAdjacent(Vector3d vectorFromThis);
        void Inverse();
        Vector3d CalGradPhi(Vector3d b);
        MatrixR3C3 ToFullMatrix();
        std::string ToString();
    };
}