#pragma once
#include "FvFace.h"
namespace LxCFD
{
    class FvPair
    {
    public:
        int O_InnCell = 0;
        int N_InnCell = 0;
        int O_Cell = 0;
        int N_Cell = 0;
        int O_Face = 0;
        int N_Face = 0;
        void SetONIndex(int OFaceId, const FvFace &OFace, int NFaceId, const FvFace &NFace);
    };
}