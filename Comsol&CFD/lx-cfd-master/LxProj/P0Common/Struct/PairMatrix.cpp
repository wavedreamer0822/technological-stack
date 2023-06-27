#include "PairMatrix.h"

namespace LxCFD
{
    void PairMatrix::Eliminate_a23a32()
    {
        double elifactor = a23 / a33;
        double a22future = a22 - elifactor * a32;
        a24 = -elifactor * a34;
        double b2future = b2 - elifactor * b3;

        elifactor = a32 / a22;
        a31 = -elifactor * a21;
        a33 -= elifactor * a23;
        b3 -= elifactor * b2;

        a22 = a22future;
        b2 = b2future;

        a23 = 0;
        a32 = 0;
    }
    void PairMatrix::Eliminate_a12a43()
    {
        double elifactor = a12 / a22;
        a11 -= elifactor * a21;
        a14 = -elifactor * a24;
        b1 -= elifactor * b2;

        elifactor = a43 / a33;
        a41 = -elifactor * a31;
        a44 -= elifactor * a34;
        b4 -= elifactor * b3;
    }
}