#include "MGMeshCreator.h"

namespace LxCFD
{
    void MGMeshCreator::Create(int maxCoarseLevelLimit, int groupNum, int maxZoneCellCount)
    {
        if (maxCoarseLevelLimit > 0)
        {
            this->maxCoarseLevelLimit = maxCoarseLevelLimit;
        }
        else
        {
            LxConsole::Error("粗网格级数必须大于0，自动更改为50");
            this->maxCoarseLevelLimit = 50;
        }
        if (groupNum > 1)
        {
            zoneCreator.TargetCoarseNum = groupNum;
        }
        else
        {
            LxConsole::Error("形成粗网格的细网格数量必须大于1，已自动更改为4");
            zoneCreator.TargetCoarseNum = 4;
        }
        zoneCreator.InCoarseCell.resize(maxZoneCellCount);
        zoneCreator.GroupCells.resize(groupNum * 10);
        zoneCreator.tempMGCell.reserve(groupNum * 2);
        zoneCreator.coarseCells = &coarseCellsCommon;
        contactCreator.contactTempCells = &coarseCellsCommon;
    }
}
