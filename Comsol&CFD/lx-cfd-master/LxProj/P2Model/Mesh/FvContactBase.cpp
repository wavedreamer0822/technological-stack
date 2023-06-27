#include "FvContactBase.h"

namespace LxCFD
{
    void FvContactBase::PrepareMeshData()
    {
        auto &OCells = OZone->Cells;
        auto &NCells = NZone->Cells;
        if (IsConode)
        {
            Pairs.clear();
            Pairs.resize(OThread->ThreadIndex.FaceIDs.GetCount());
            ShallowArrayStorage.Initialize(1, Pairs.size());
            int deltaOFaceId = OThread->ThreadIndex.FaceIDs.Start;
            int deltaNFaceId = NThread->ThreadIndex.FaceIDs.Start;
            int deltaOCellId = OThread->ThreadIndex.CellIDs.Start;
            int deltaNCellId = NThread->ThreadIndex.CellIDs.Start;
            for (std::size_t i1 = 0; i1 < Pairs.size(); ++i1)
            {
                std::vector<int> v;
                v.push_back(i1);
                Pairs.at(i1).SetONIndex(i1 + deltaOFaceId, OZone->Faces.at(i1 + deltaOFaceId), i1 + deltaNFaceId, NZone->Faces.at(i1 + deltaNFaceId));
                OCells.at(i1 + deltaOCellId).OFaces = ShallowArrayStorage.Create(v);
                NCells.at(i1 + deltaNCellId).OFaces = ShallowArrayStorage.Create(v);
            }
            InnerIndex = IndexNumber(0, Pairs.size() - 1, 0, Pairs.size() - 1);
        }
        else
        {
            LxConsole::Error("暂不支持非共节点界面");
        }
    }
    ShortArray::Shallow &FvContactBase::GetOZoneCellOFaces(int cellID)
    {
        return OZone->Cells.at(cellID).OFaces;
    }
    ShortArray::Shallow &FvContactBase::GetNZoneCellOFaces(int cellID)
    {
        return NZone->Cells.at(cellID).OFaces;
    }
    IndexNumber &FvContactBase::GetInnerIndex()
    {
        return InnerIndex;
    }

}