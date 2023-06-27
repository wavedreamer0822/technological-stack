#pragma once
#include "MGZoneCreator.h"
#include "MGContactCreator.h"
#include "QueueTool.h"
namespace LxCFD
{
    class MGMeshCreator
    {
    public:
        int maxCoarseLevelLimit;
        MGZoneCreator zoneCreator;
        MGContactCreator contactCreator;
        std::vector<MGCellTemp> coarseCellsCommon;

        void Create(int maxCoarseLevelLimit, int groupNum, int maxZoneCellCount);
    };
}
