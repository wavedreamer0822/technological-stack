#include "MatrixR3C3.h"

namespace LxCFD
{
    MatrixR3C3::MatrixR3C3() {}
    MatrixR3C3::MatrixR3C3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
        : a11(a11), a12(a12), a13(a13), a21(a21), a22(a22), a23(a23), a31(a31), a32(a32), a33(a33) {}
    void MatrixR3C3::Inverse()
    {
        double A_norm = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 - a12 * a21 * a33 - a11 * a23 * a32;
        double A11 = a22 * a33 - a32 * a23;
        double A12 = -(a12 * a33 - a13 * a32);
        double A13 = a12 * a23 - a13 * a22;
        double A21 = -(a21 * a33 - a31 * a23);
        double A22 = a11 * a33 - a13 * a31;
        double A23 = -(a11 * a23 - a21 * a13);
        double A31 = a32 * a21 - a22 * a31;
        double A32 = -(a11 * a32 - a31 * a12);
        double A33 = a11 * a22 - a21 * a12;

        a11 = A11 / A_norm;
        a12 = A12 / A_norm;
        a13 = A13 / A_norm;
        a21 = A21 / A_norm;
        a22 = A22 / A_norm;
        a23 = A23 / A_norm;
        a31 = A31 / A_norm;
        a32 = A32 / A_norm;
        a33 = A33 / A_norm;
    }
    MatrixR3C3 MatrixR3C3::Product(MatrixR3C3 matrix1, MatrixR3C3 matrix2)
    {
        MatrixR3C3 m;
        m.a11 = matrix1.a11 * matrix2.a11 + matrix1.a12 * matrix2.a21 + matrix1.a13 * matrix2.a31;
        m.a12 = matrix1.a11 * matrix2.a12 + matrix1.a12 * matrix2.a22 + matrix1.a13 * matrix2.a32;
        m.a13 = matrix1.a11 * matrix2.a13 + matrix1.a12 * matrix2.a23 + matrix1.a13 * matrix2.a33;
        m.a21 = matrix1.a21 * matrix2.a11 + matrix1.a22 * matrix2.a21 + matrix1.a23 * matrix2.a31;
        m.a22 = matrix1.a21 * matrix2.a12 + matrix1.a22 * matrix2.a22 + matrix1.a23 * matrix2.a32;
        m.a23 = matrix1.a21 * matrix2.a13 + matrix1.a22 * matrix2.a23 + matrix1.a23 * matrix2.a33;
        m.a31 = matrix1.a31 * matrix2.a11 + matrix1.a32 * matrix2.a21 + matrix1.a33 * matrix2.a31;
        m.a32 = matrix1.a31 * matrix2.a12 + matrix1.a32 * matrix2.a22 + matrix1.a33 * matrix2.a32;
        m.a33 = matrix1.a31 * matrix2.a13 + matrix1.a32 * matrix2.a23 + matrix1.a33 * matrix2.a33;
        return m;
    }
    std::string MatrixR3C3::ToString()
    {
        std::stringstream ss;
        ss << a11 << "," << a12 << "," << a13 << std::endl
           << a21 << "," << a22 << "," << a23 << std::endl
           << a31 << "," << a32 << "," << a33 << std::endl;
        return ss.str();
    }
}