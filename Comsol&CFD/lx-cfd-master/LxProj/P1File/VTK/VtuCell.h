#pragma once
#include <vector>
#include "FvCell.h"
#include "FvFace.h"

namespace LxCFD
{
    struct VtuCell
    {
    public:
        ShortArray::Shallow Connect;
        int OffSet;
        unsigned int Type;
        bool AddCellInf_bound(const FvCell &fvCell, const std::vector<FvFace> &faces, ShortArray::Deep &store, int &iniOffset);
        bool AddCellInf_inner(const FvCell &fvCell, const std::vector<FvFace> &faces, ShortArray::Deep &store, int &iniOffset);
        void AddFirstFace_Forward(const FvFace &face, int &nodeFlag);
        void AddFirstFace_Reverse(const FvFace &face, int &nodeFlag);
        void AddFace_3Nodes(const FvFace &face, int &nodeFlag);
        void AddFace_4Nodes(const FvFace &face);
        int InConnect(int nodeID);
    };
}