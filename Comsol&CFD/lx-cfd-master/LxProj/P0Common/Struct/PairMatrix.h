#pragma once

namespace LxCFD
{
    class PairMatrix
    {
    public:
        double a11 = 0;
        double a12 = 0;
        double a14 = 0;
        double b1 = 0;
        double a21 = 0;
        double a22 = 0;
        double a23 = 0;
        double a24 = 0;
        double b2 = 0;
        double a31 = 0;
        double a32 = 0;
        double a33 = 0;
        double a34 = 0;
        double b3 = 0;
        double a41 = 0;
        double a43 = 0;
        double a44 = 0;
        double b4 = 0;
        void Eliminate_a23a32();
        void Eliminate_a12a43();
    };
}