#include "FvZoneBase.h"
#include "QueueTool.h"
namespace LxCFD
{
    void FvZoneBase::PrepareMeshData()
    {
        CreatCells();
        CalZoneGeometry();
        CalTotalVolumnArea();
        CellCommonArray.resize(Cells.size());
        FaceCommonArray.resize(std::max(Cells.size(), Faces.size()));
    }
    void FvZoneBase::CreatCells()
    {
        Cells.resize(TotalIndex.CellIDs.GetCount());
        QueueTool oqt, nqt;
        oqt.Resize(Cells.size(), Faces.size());
        nqt.Resize(Cells.size(), Faces.size());
        for (std::size_t i1 = 0; i1 < Faces.size(); ++i1)
        {
            FvFace &f = Faces.at(i1);
            oqt.AddOneToQueue(f.OSideCell, i1);
            nqt.AddOneToQueue(f.NSideCell, i1);
        }
        for (std::size_t i1 = 0; i1 < Cells.size(); ++i1)
        {
            FvCell &c = Cells.at(i1);
            oqt.ConvertQueueToArray(c.OFaces, ShallowArrayStorage, i1);
            nqt.ConvertQueueToArray(c.NFaces, ShallowArrayStorage, i1);
        }
    }

    void FvZoneBase::CalZoneGeometry()
    {
        {
            for (std::size_t i1 = 0; i1 < Faces.size(); ++i1)
            {
                Faces.at(i1).CalGeometryInFace(*Nodes);
            }
        }
        {
            int i1 = 0;
            for (; i1 <= InnerIndex.CellIDs.End; ++i1)
            {
                Cells.at(i1).CalGeometry_inner(Faces);
            }
            for (size_t i2 = i1; i2 < Cells.size(); ++i2)
            {
                Cells.at(i2).CalGeometry_bound(Faces);
            }
        }
        {
            int i1 = 0;
            for (; i1 <= InnerIndex.FaceIDs.End; ++i1)
            {
                Faces.at(i1).CalGeometryAcrossFace_inner(Cells);
            }
            for (std::size_t i2 = i1; i2 < Faces.size(); ++i2)
            {
                Faces.at(i2).CalGeometryAcrossFace_bound(Cells);
            }
        }
        {
            for (std::size_t i1 = 0; i1 < Cells.size(); ++i1)
            {
                Cells.at(i1).CalMatrix_LeastSquare(Faces);
            }
        }
    }
    void FvZoneBase::CalTotalVolumnArea()
    {
        Volumn = 0;
        int endID = InnerIndex.CellIDs.End;
        for (int i1 = InnerIndex.CellIDs.Start; i1 <= endID; ++i1)
        {
            Volumn += Cells.at(i1).Volumn;
        }
        for (auto &b : BoundThreads)
        {
            double area = 0;
            IndexRecorder &faceIDs = b->ThreadIndex.FaceIDs;
            for (int i3 = faceIDs.Start; i3 <= faceIDs.End; ++i3)
            {
                area += Faces.at(i3).Area;
            }
            b->Area = area;
        }
        // int threadCount = GetThreadCount();
        // for (int i2 = 0; i2 < threadCount; i2++)
        // {
        //     double area = 0;
        //     auto &b = GetThread(i2);
        //     IndexNumber &bindex = b.ThreadIndex;
        //     endID = bindex.FaceIDs.End;
        //     for (int i3 = bindex.FaceIDs.Start; i3 <= endID; ++i3)
        //     {
        //         area += Faces.at(i3).Area;
        //     }
        //     b.Area = area;
        // }
    }

    // region IProvideZoneTopology
    ShortArray::Shallow &FvZoneBase::GetCellOFaces(int CellIndex)
    {
        return Cells.at(CellIndex).OFaces;
    }
    ShortArray::Shallow &FvZoneBase::GetCellNFaces(int CellIndex)
    {
        return Cells.at(CellIndex).NFaces;
    }
    int FvZoneBase::GetFaceOSideCell(int FaceIndex)
    {
        return Faces.at(FaceIndex).OSideCell;
    }
    int FvZoneBase::GetFaceNSideCell(int FaceIndex)
    {
        return Faces.at(FaceIndex).NSideCell;
    }
    ONPair FvZoneBase::GetONCellID(int FaceIndex)
    {
        return Faces.at(FaceIndex).GetONCellID();
    }
    IndexNumber &FvZoneBase::GetInnerIndex()
    {
        return InnerIndex;
    }
    IndexNumber &FvZoneBase::GetTotalIndex()
    {
        return TotalIndex;
    }
    IndexNumber &FvZoneBase::GetThreadIndex(int threadID)
    {
        return BoundThreads.at(threadID)->ThreadIndex;
    }
    // endregion
    int FvZoneBase::GetVariableCount()
    {
        return Cells.size();
    }

    int FvZoneBase::GetThreadCount()
    {
        return BoundThreads.size();
    }

}