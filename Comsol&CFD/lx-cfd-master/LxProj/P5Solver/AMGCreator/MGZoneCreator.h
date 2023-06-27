#pragma once
#include "MGCellTemp.h"
#include "IProvideZoneTopology.h"
#include "MGZone.h"
#include "QueueTool.h"
#include "LinkArray.h"
namespace LxCFD
{
    class MGZoneCreator
    {
    public:
        int TargetCoarseNum;
        std::vector<int> InCoarseCell;
        std::vector<int> GroupCells;
        std::vector<int> tempMGCell;
        MGZone *coarseZone;
        std::vector<MGCellTemp> *coarseCells;
        std::vector<MGFaceTemp> coarseFaces;

        LinkArray<MGFaceTemp>::Deep LinkArray_MGFaceTemp;
        LinkArray<int>::Deep LinkArray_Int;
        std::unique_ptr<MGZone> CreateMGZone(IProvideZoneTopology *finezone);

    protected:
        //Flag----
        const int Flag_InNone_Inner = -3;
        const int Flag_InNone_Bound = -4;
        const int Flag_InGroup = -2;
        const int Flag_InTempCell = -1;
        bool Flag_IsInCreatedCells(int newID)
        {
            return newID >= 0;
        }
        //Flag----end
        IProvideZoneTopology *finezone;
        int editPos;

        void initialize();
        void createInnerMGCells();
        void createGroupAndSplitCell(int startCell);
        bool tryCreateGroup(int cellIndex);
        void splitGroup();
        void splitMGCell(int startCell);
        void addTempCellToList();
        bool trySplitMGCell(int adjcell);
        void createInnerCoarseFaces();
        void AddFace(int i1, ONPair onnew);
        void createBoundCoarseFacesAndCells(IndexNumber &fineThreadIndex);
        void splitCoarseFacesFromCellStorageToList();
        void addCoarseFaceAndCellToCoarseZone();
        void checkTopology();
    };
}