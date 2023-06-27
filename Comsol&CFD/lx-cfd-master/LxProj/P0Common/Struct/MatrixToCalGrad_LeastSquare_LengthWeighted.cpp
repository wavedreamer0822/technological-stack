#include "MatrixToCalGrad_LeastSquare_LengthWeighted.h"

namespace LxCFD
{
    void MatrixToCalGrad_LeastSquare_LengthWeighted::AddVector_FromThisToAdjacent(Vector3d vectorFromThis)
    {
        double lengthWeight = 1 / vectorFromThis.CalLength();
        a11 += lengthWeight * vectorFromThis.X * vectorFromThis.X;
        a22 += lengthWeight * vectorFromThis.Y * vectorFromThis.Y;
        a33 += lengthWeight * vectorFromThis.Z * vectorFromThis.Z;
        a21 += lengthWeight * vectorFromThis.X * vectorFromThis.Y;
        a31 += lengthWeight * vectorFromThis.X * vectorFromThis.Z;
        a32 += lengthWeight * vectorFromThis.Y * vectorFromThis.Z;
    }
    void MatrixToCalGrad_LeastSquare_LengthWeighted::Inverse()
    {
        double A_norm = a11 * a22 * a33 + a21 * a32 * a31 * 2 - a31 * a22 * a31 - a21 * a21 * a33 - a11 * a32 * a32;
        //1.暂时存储代数余子式的值
        double A11 = a22 * a33 - a32 * a32;
        double A21 = -(a21 * a33 - a31 * a32);
        double A22 = a11 * a33 - a31 * a31;
        double A31 = a32 * a21 - a22 * a31;
        double A32 = -(a11 * a32 - a31 * a21);
        double A33 = a11 * a22 - a21 * a21;
        //2.完全计算出A^-1
        a11 = A11 / A_norm;
        a21 = A21 / A_norm;
        a22 = A22 / A_norm;
        a31 = A31 / A_norm;
        a32 = A32 / A_norm;
        a33 = A33 / A_norm;
    }
    Vector3d MatrixToCalGrad_LeastSquare_LengthWeighted::CalGradPhi(Vector3d b)
    {
        return Vector3d(
            a11 * b.X + a21 * b.Y + a31 * b.Z,
            a21 * b.X + a22 * b.Y + a32 * b.Z,
            a31 * b.X + a32 * b.Y + a33 * b.Z);
    }
    MatrixR3C3 MatrixToCalGrad_LeastSquare_LengthWeighted::ToFullMatrix()
    {
        return MatrixR3C3(a11, a21, a31, a21, a22, a32, a31, a32, a33);
    }
    std::string MatrixToCalGrad_LeastSquare_LengthWeighted::ToString()
    {
        MatrixR3C3 m = ToFullMatrix();
        return m.ToString();
    }
}