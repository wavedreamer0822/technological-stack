#pragma once
#include <vector>
#include "ONPair.h"
#include "ShortArray.h"

namespace LxCFD
{
    struct MGFace
    {
    public:
        int OSideCell = 0;
        int NSideCell = 0;
        ShortArray::Shallow FineFaces_O2N; //粗面由细网格面组成，此处标识出细面中owner neighbor关系与粗面一致的面数
        ShortArray::Shallow FineFaces_N2O;
        //void Set(const std::vector<int> fineFaces_O2N, const std::vector<int> fineFaces_N2O, int oSideCell, int nSideCell);
        inline ONPair GetONCellID()
        {
            return ONPair(OSideCell, NSideCell);
        }
    };
}