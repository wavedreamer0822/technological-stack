#include "MGZoneCreator.h"
#include <sstream>
#include <cmath>
namespace LxCFD
{
    std::unique_ptr<MGZone> MGZoneCreator::CreateMGZone(IProvideZoneTopology *finezone)
    {
        this->finezone = finezone;
        std::unique_ptr<MGZone> mgZone = std::unique_ptr<MGZone>(new MGZone());
        coarseZone = mgZone.get();

        initialize();
        createInnerMGCells();
        createInnerCoarseFaces();
        for (int i1 = 0; i1 < finezone->GetThreadCount(); ++i1)
        {
            createBoundCoarseFacesAndCells(finezone->GetThreadIndex(i1));
        }
        addCoarseFaceAndCellToCoarseZone();
        //checkTopology();
        coarseCells->clear();
        coarseFaces.clear();
        return std::move(mgZone);
    }
    void MGZoneCreator::initialize()
    {
        int fineCellCount = finezone->GetTotalIndex().CellIDs.GetCount();
        InCoarseCell.resize(fineCellCount);
        coarseZone->ShallowArrayStorage.Initialize(4, fineCellCount);
        LinkArray_Int.Initialize(5, fineCellCount);
        LinkArray_MGFaceTemp.Initialize(5, fineCellCount);
        coarseCells->reserve(fineCellCount);
        coarseFaces.reserve(finezone->GetTotalIndex().FaceIDs.GetCount());

        IndexRecorder cellIDs;
        cellIDs = finezone->GetInnerIndex().CellIDs;
        for (int i1 = cellIDs.Start; i1 <= cellIDs.End; ++i1)
        {
            InCoarseCell.at(i1) = Flag_InNone_Inner; //内部初始
        }
        for (int i1 = 0; i1 < finezone->GetThreadCount(); ++i1)
        {
            cellIDs = finezone->GetThreadIndex(i1).CellIDs;
            for (int i2 = cellIDs.Start; i2 <= cellIDs.End; i2++)
            {
                InCoarseCell.at(i2) = Flag_InNone_Bound; //边界初始
            }
        }
    }
    void MGZoneCreator::createInnerMGCells()
    {
        const IndexRecorder &cellIDs = finezone->GetInnerIndex().CellIDs;
        int zoneStartId = finezone->GetThreadIndex(0).FaceIDs.Start;
        zoneStartId = finezone->GetFaceOSideCell(zoneStartId);
        editPos = 0;
        for (int i1 = zoneStartId; i1 <= cellIDs.End; ++i1)
        {
            createGroupAndSplitCell(i1);
        }
        for (int i1 = cellIDs.Start; i1 < zoneStartId; ++i1)
        {
            createGroupAndSplitCell(i1);
        }
    }
    void MGZoneCreator::createGroupAndSplitCell(int startCell)
    {
        if (!tryCreateGroup(startCell))
            return;
        int searchPos = 0;
        int searchEndp1 = editPos;
        while (searchPos < searchEndp1)
        {
            for (; searchPos < searchEndp1; ++searchPos)
            {
                for (int &adjFace : finezone->GetCellOFaces(GroupCells[searchPos]))
                {
                    int adjcell = finezone->GetFaceNSideCell(adjFace);
                    if (tryCreateGroup(adjcell) && editPos == (int)GroupCells.size())
                    {
                        splitGroup();
                        return;
                    }
                }
                for (int &adjFace : finezone->GetCellNFaces(GroupCells[searchPos]))
                {
                    int adjcell = finezone->GetFaceOSideCell(adjFace);
                    if (tryCreateGroup(adjcell) && editPos == (int)GroupCells.size())
                    {
                        splitGroup();
                        return;
                    }
                }
            }
            searchEndp1 = editPos;
        }
        splitGroup();
    }
    bool MGZoneCreator::tryCreateGroup(int cellIndex)
    {
        int &inCoarse = InCoarseCell.at(cellIndex);
        if (inCoarse == Flag_InNone_Inner)
        {
            inCoarse = Flag_InGroup;
            GroupCells.at(editPos) = cellIndex;
            ++editPos;
            return true;
        }
        else
        {
            return false;
        }
    }
    void MGZoneCreator::splitGroup()
    {
        editPos--;
        for (; editPos >= 0; editPos--)
        {
            splitMGCell(GroupCells[editPos]);
        }
        editPos = 0;
    }
    void MGZoneCreator::splitMGCell(int startCell)
    {
        if (!trySplitMGCell(startCell))
            return;
        int searchPos = 0;
        int searchEndp1 = tempMGCell.size();
        while (searchPos < searchEndp1)
        {
            for (; searchPos < searchEndp1; ++searchPos)
            {
                for (int &adjFace : finezone->GetCellOFaces(tempMGCell[searchPos]))
                {
                    int adjcell = finezone->GetFaceNSideCell(adjFace);
                    if (trySplitMGCell(adjcell) && (int)tempMGCell.size() >= TargetCoarseNum)
                    {
                        addTempCellToList();
                        return;
                    }
                }
                for (int &adjFace : finezone->GetCellNFaces(tempMGCell[searchPos]))
                {
                    int adjcell = finezone->GetFaceOSideCell(adjFace);
                    if (trySplitMGCell(adjcell) && (int)tempMGCell.size() >= TargetCoarseNum)
                    {
                        addTempCellToList();
                        return;
                    }
                }
            }
            searchEndp1 = tempMGCell.size();
        }
        if (tempMGCell.size() > 0.5 * TargetCoarseNum)
        {
            addTempCellToList();
        }
        else
        {
            int adjCoarsecell = 0;
            int adjCoarsecellfinecount = std::numeric_limits<int>::max(); // int.MaxValue;
            for (int &fc : tempMGCell)
            {
                for (int &adjFace : finezone->GetCellOFaces(fc))
                {
                    int adjcell = finezone->GetFaceNSideCell(adjFace);
                    int newID = InCoarseCell.at(adjcell);
                    if (Flag_IsInCreatedCells(newID))
                    {
                        int fineCellsCount = coarseCells->at(newID).FineCells.Length; 
                        if (fineCellsCount < adjCoarsecellfinecount)
                        {
                            adjCoarsecellfinecount = fineCellsCount;
                            adjCoarsecell = newID;
                        }
                    }
                }
                for (int &adjFace : finezone->GetCellNFaces(fc))
                {
                    int adjcell = finezone->GetFaceOSideCell(adjFace);
                    int newID = InCoarseCell.at(adjcell);
                    if (Flag_IsInCreatedCells(newID))
                    {
                        int fineCellsCount = coarseCells->at(newID).FineCells.Length; 
                        if (fineCellsCount < adjCoarsecellfinecount)
                        {
                            adjCoarsecellfinecount = fineCellsCount;
                            adjCoarsecell = newID;
                        }
                    }
                }
            }
            if (adjCoarsecellfinecount == std::numeric_limits<int>::max())
            {
                addTempCellToList();
            }
            else
            {
                MGCellTemp &cell = coarseCells->at(adjCoarsecell);
                for (int &fc : tempMGCell)
                {
                    InCoarseCell.at(fc) = adjCoarsecell;
                    LinkArray_Int.CreateAdd(cell.FineCells, fc);
                }
                tempMGCell.clear();
            }
        }
    }
    void MGZoneCreator::addTempCellToList()
    {
        int coarseIndex = coarseCells->size();
        coarseCells->push_back(MGCellTemp());
        MGCellTemp &cell = coarseCells->back();
        for (int &fc : tempMGCell)
        {
            InCoarseCell.at(fc) = coarseIndex;
            LinkArray_Int.CreateAdd(cell.FineCells, fc);
        }
        tempMGCell.clear();
    }
    bool MGZoneCreator::trySplitMGCell(int adjcell)
    {
        int &inCoarse = InCoarseCell.at(adjcell);
        if (inCoarse == Flag_InGroup)
        {
            tempMGCell.push_back(adjcell);
            inCoarse = Flag_InTempCell;
            return true;
        }
        return false;
    }

    void MGZoneCreator::createInnerCoarseFaces()
    {
        IndexRecorder faceIDs = finezone->GetInnerIndex().FaceIDs;
        for (int i1 = faceIDs.Start; i1 <= faceIDs.End; ++i1)
        {
            ONPair onfinemesh = finezone->GetONCellID(i1);
            ONPair onnew = ONPair(
                InCoarseCell.at(onfinemesh.Owner),
                InCoarseCell.at(onfinemesh.Neighbor));

            if (onnew.Owner == onnew.Neighbor)
            {
                LinkArray_Int.CreateAdd(coarseCells->at(onnew.Owner).InnerFineFaces, i1);
            }
            else
            {
                AddFace(i1, onnew);
            }
        }
        splitCoarseFacesFromCellStorageToList();
        coarseZone->InnerIndex = IndexNumber(0, coarseCells->size() - 1, 0, coarseFaces.size() - 1);
    }
    void MGZoneCreator::AddFace(int i1, ONPair onnew)
    {
        if (onnew.Owner < onnew.Neighbor) //默认Face存储到小编号的粗网格中
        {
            auto &storage = coarseCells->at(onnew.Owner).CoarseOFacesStorage;
            for (auto &ccf : storage)
            {
                if (ccf.NeighborCellIndex == onnew.Neighbor)
                {
                    LinkArray_Int.CreateAdd(ccf.FineFace_O2N, i1);
                    return;
                }
            }
            LinkArray_MGFaceTemp.CreateAdd(storage, MGFaceTemp());
            MGFaceTemp &ccfnew = (*storage.Last).Value;
            ccfnew.OwnerCellIndex = onnew.Owner;
            ccfnew.NeighborCellIndex = onnew.Neighbor;
            LinkArray_Int.CreateAdd(ccfnew.FineFace_O2N, i1); 
        }
        else
        {
            auto &storage = coarseCells->at(onnew.Neighbor).CoarseOFacesStorage;
            for (auto &ccf : storage)
            {
                if (ccf.NeighborCellIndex == onnew.Owner)
                {
                    LinkArray_Int.CreateAdd(ccf.FineFace_N2O, i1);
                    return;
                }
            }
            LinkArray_MGFaceTemp.CreateAdd(storage, MGFaceTemp());
            MGFaceTemp &ccfnew = (*storage.Last).Value;
            ccfnew.OwnerCellIndex = onnew.Neighbor;
            ccfnew.NeighborCellIndex = onnew.Owner;
            LinkArray_Int.CreateAdd(ccfnew.FineFace_N2O, i1);
        }
    }
    void MGZoneCreator::createBoundCoarseFacesAndCells(IndexNumber &fineThreadIndex)
    {
        //先创建face，face暂时存储在临时数据
        int startCellId = coarseCells->size(), startFaceId = coarseFaces.size();
        IndexRecorder faceIDs = fineThreadIndex.FaceIDs;
        for (int i1 = faceIDs.Start; i1 <= faceIDs.End; ++i1)
        {
            int fineO = finezone->GetFaceOSideCell(i1);
            int coarseOwner = InCoarseCell[fineO];
            auto &storage = coarseCells->at(coarseOwner).CoarseOFacesStorage;
            if (storage.Length == 0)
            {
                LinkArray_MGFaceTemp.CreateAdd(storage, MGFaceTemp());
                MGFaceTemp &coarsefacetemp = (*storage.Last).Value;
                coarsefacetemp.OwnerCellIndex = coarseOwner,
                LinkArray_Int.CreateAdd(coarsefacetemp.FineFace_O2N, i1);
            }
            else
            {
                MGFaceTemp &coarsefacetemp = (*storage.Last).Value;
                LinkArray_Int.CreateAdd(coarsefacetemp.FineFace_O2N, i1);
            }
        }
        //后从coarsecell中找到刚刚添加的面，转移到coarseFace中
        splitCoarseFacesFromCellStorageToList();
        //最后补充coarseCell
        for (std::size_t i1 = startFaceId; i1 < coarseFaces.size(); ++i1)
        {
            auto &coarseFace = coarseFaces.at(i1);
            coarseFace.NeighborCellIndex = coarseCells->size();
            //创建粗Cell
            coarseCells->push_back(MGCellTemp());
            MGCellTemp &threadcoarsecell = coarseCells->back();
            for (auto &f : coarseFace.FineFace_O2N)
            {
                LinkArray_Int.CreateAdd(threadcoarsecell.FineCells, finezone->GetFaceNSideCell(f));
            }
        }
        IndexNumber coarseIndex = IndexNumber(startCellId, coarseCells->size() - 1, startFaceId, coarseFaces.size() - 1);
        coarseZone->ThreadIndexs.push_back(coarseIndex);
    }
    void MGZoneCreator::splitCoarseFacesFromCellStorageToList()
    {
        for (MGCellTemp &coarsecell : *coarseCells)
        {
            if (coarsecell.CoarseOFacesStorage.Length != 0)
            {
                for (auto &cf : coarsecell.CoarseOFacesStorage)
                {
                    coarseFaces.push_back(cf);
                }
                coarsecell.CoarseOFacesStorage.Clear();
            }
        }
    }
    void MGZoneCreator::addCoarseFaceAndCellToCoarseZone()
    {
        auto &store = coarseZone->ShallowArrayStorage;
        //添加face信息
        auto &structFaces = coarseZone->Faces;
        structFaces.resize(coarseFaces.size());
        for (std::size_t i1 = 0; i1 < structFaces.size(); ++i1)
        {
            MGFaceTemp &temp = coarseFaces.at(i1);
            MGFace &target = structFaces.at(i1);
            target.OSideCell = temp.OwnerCellIndex;
            target.NSideCell = temp.NeighborCellIndex;
            target.FineFaces_O2N = store.Create(temp.FineFace_O2N);
            target.FineFaces_N2O = store.Create(temp.FineFace_N2O);
            LinkArray_Int.CreateAdd(coarseCells->at(temp.OwnerCellIndex).FacesAtO, i1);
            LinkArray_Int.CreateAdd(coarseCells->at(temp.NeighborCellIndex).FacesAtN, i1);
        }
        //添加cell信息
        auto &structCells = coarseZone->Cells;
        structCells.resize(coarseCells->size());
        for (std::size_t i1 = 0; i1 < structCells.size(); ++i1)
        {
            MGCell &cell = structCells.at(i1);
            MGCellTemp &mgcell = coarseCells->at(i1);
            cell.FineCells = store.Create(mgcell.FineCells);
            cell.InnerFineFaces = store.Create(mgcell.InnerFineFaces);
            cell.OFaces=store.Create(mgcell.FacesAtO);
            cell.NFaces=store.Create(mgcell.FacesAtN);
        }
        coarseZone->TotalIndex = IndexNumber(0, coarseZone->Cells.size() - 1, 0, coarseZone->Faces.size() - 1);
    }
    void MGZoneCreator::checkTopology()
    {
        for (auto &coarseIndex : coarseZone->ThreadIndexs)
        {
            for (int i1 = coarseIndex.CellIDs.Start; i1 <= coarseIndex.CellIDs.End; ++i1)
            {
                for (auto &fc : coarseZone->Cells.at(i1).FineCells)
                {
                    InCoarseCell[fc] = i1;
                }
            }
        }
        IndexNumber FineInnerIndex = finezone->GetInnerIndex();
        int fineFaceCountInFineZone = 0, fineCellCountInFineZone = 0;
        fineCellCountInFineZone += FineInnerIndex.CellIDs.GetCount();
        fineFaceCountInFineZone += FineInnerIndex.FaceIDs.GetCount();
        for (int i1 = 0; i1 < finezone->GetThreadCount(); ++i1)
        {
            IndexNumber ind = finezone->GetThreadIndex(i1);
            fineCellCountInFineZone += ind.CellIDs.GetCount(); // ind.CellIDs.End - ind.CellIDs.Start + 1;
            fineFaceCountInFineZone += ind.FaceIDs.GetCount(); // ind.FaceIDs.End - ind.FaceIDs.Start + 1;
        }
        int fineCellCountInCoarse = 0;
        for (std::size_t i1 = 0; i1 < coarseZone->Cells.size(); ++i1)
        {
            for (int i2 = 0; i2 < coarseZone->Cells[i1].FineCells.GetLengh(); i2++)
            {
                fineCellCountInCoarse++;
                if (InCoarseCell[coarseZone->Cells[i1].FineCells[i2]] != (int)i1)
                {
                    std::stringstream ss;
                    ss << "AMG error in coarse " << i1 << " in fine " << coarseZone->Cells[i1].FineCells[i2];
                    LxConsole::Error(ss.str());
                }
            }
        }
        if (fineCellCountInCoarse != fineCellCountInFineZone)
        {
            std::stringstream ss;
            ss << "AMG error  finecellcount inIndex:" << fineCellCountInFineZone << " inCoarse:" << fineCellCountInCoarse;
            LxConsole::Error(ss.str());
        }
        for (std::size_t i1 = 0; i1 < coarseZone->Cells.size(); ++i1) //检查粗网格面与网格对应关系
        {
            for (int i2 = 0; i2 < coarseZone->Cells[i1].OFaces.GetLengh(); i2++)
            {
                if (coarseZone->Faces[coarseZone->Cells[i1].OFaces[i2]].OSideCell != (int)i1)
                {
                    std::stringstream ss;
                    ss << "AMG error in coarseface";
                    LxConsole::Error(ss.str());
                }
            }
            for (int i2 = 0; i2 < coarseZone->Cells[i1].NFaces.GetLengh(); i2++)
            {
                if (coarseZone->Faces[coarseZone->Cells[i1].NFaces[i2]].NSideCell != (int)i1)
                {
                    LxConsole::Error("AMG error in coarseface");
                }
            }
        }
        int fineFaceCountInCoarse = 0;
        for (std::size_t i1 = 0; i1 < coarseZone->Cells.size(); ++i1) //检查粗网格内部面
        {
            for (auto &ii : coarseZone->Cells[i1].InnerFineFaces)
            {
                fineFaceCountInCoarse++;
                ONPair on = finezone->GetONCellID(ii);
                if (InCoarseCell[on.Owner] != (int)i1 || InCoarseCell[on.Neighbor] != (int)i1)
                {
                    LxConsole::Error("AMG error in face");
                }
            }
        }
        for (std::size_t i1 = 0; i1 < coarseZone->Faces.size(); ++i1) //检查粗网格交界面
        {
            for (int i2 = 0; i2 < coarseZone->Faces[i1].FineFaces_O2N.GetLengh(); i2++)
            {
                fineFaceCountInCoarse++;
                ONPair on = finezone->GetONCellID(coarseZone->Faces[i1].FineFaces_O2N[i2]);
                if (InCoarseCell[on.Owner] != coarseZone->Faces[i1].OSideCell || InCoarseCell[on.Neighbor] != coarseZone->Faces[i1].NSideCell)
                    LxConsole::Error("AMG error in face");
            }
            for (int i2 = 0; i2 < coarseZone->Faces[i1].FineFaces_N2O.GetLengh(); i2++)
            {
                fineFaceCountInCoarse++;
                ONPair on = finezone->GetONCellID(coarseZone->Faces[i1].FineFaces_N2O[i2]);
                if (InCoarseCell[on.Owner] != coarseZone->Faces[i1].NSideCell || InCoarseCell[on.Neighbor] != coarseZone->Faces[i1].OSideCell)
                    LxConsole::Error("AMG error in face");
            }
        }
        if (fineFaceCountInCoarse != fineFaceCountInFineZone)
        {
            std::stringstream ss;
            ss << "AMG error finefacecount inIndex:" << fineFaceCountInFineZone << "inCoarse:" << fineFaceCountInCoarse;
            LxConsole::Error(ss.str());
        }
    }
}
