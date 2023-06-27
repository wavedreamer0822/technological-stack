#pragma once
#include <vector>
#include "MGFace.h"
#include "LinkArray.h"
namespace LxCFD
{
    class MGFaceTemp
    {
    public:
        //MGFaceTemp();
        int OwnerCellIndex;
        int NeighborCellIndex;
        LinkArray<int>::List FineFace_O2N;
        LinkArray<int>::List FineFace_N2O;
        //void ConverterToCoarseFace(MGFace &target);
    };
}
// std::vector<int> FineFace_O2N;
// std::vector<int> FineFace_N2O;