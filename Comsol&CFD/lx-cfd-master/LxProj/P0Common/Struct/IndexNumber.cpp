#include "IndexNumber.h"
#include <sstream>

namespace LxCFD
{
    IndexNumber::IndexNumber() {}
    IndexNumber::IndexNumber(int startCellID, int endCellID, int startFaceID, int endFaceID) : CellIDs(startCellID, endCellID), FaceIDs(startFaceID, endFaceID) {}
    std::string IndexNumber::ToString()
    {
        std::stringstream ss;
        ss << "cells(" << CellIDs.Start << "~" << CellIDs.End << "),faces("<< FaceIDs.Start << "~" << FaceIDs.End<<")";
        return ss.str();
    }
    void IndexNumber::Print()
    {
        std::cout << ToString() << std::endl;
    }
}