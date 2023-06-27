#pragma once
#include <vector>
#include "ShortArray.h"

namespace LxCFD
{
    struct MGPair
    {
    public:
        int O_InnCell;
        int N_InnCell;
        int O_Cell;
        int N_Cell;
        int O_Face;
        int N_Face;
        ShortArray::Shallow FinePairs;
    };
}