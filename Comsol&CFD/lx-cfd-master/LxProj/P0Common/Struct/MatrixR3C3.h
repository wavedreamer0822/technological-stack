#pragma once
#include <string>
#include <sstream>
#include <iostream>

namespace LxCFD
{
    struct MatrixR3C3
    {
    public:
        MatrixR3C3() ;
        MatrixR3C3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);
        double a11 = 0;
        double a12 = 0;
        double a13 = 0;

        double a21 = 0;
        double a22 = 0;
        double a23 = 0;

        double a31 = 0;
        double a32 = 0;
        double a33 = 0;

        void Inverse();
        static MatrixR3C3 Product(MatrixR3C3 matrix1, MatrixR3C3 matrix2);
        std::string ToString();
    };
}