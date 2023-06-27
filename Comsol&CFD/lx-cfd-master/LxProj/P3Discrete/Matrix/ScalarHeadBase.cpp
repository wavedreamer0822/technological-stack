#include "MatrixADbBase.h"
#include "FvZone.h"
namespace LxCFD
{
    void ScalarHeadBase::CheckCreate(FvZone &zone)
    {
        Zone = &zone;
        Faces = &zone.Faces;
        Cells = &zone.Cells;
        InnerIndex = &zone.InnerIndex;
        TotalIndex = &zone.TotalIndex;
        x_Common = &zone.CellCommonArray;
        b_FaceCommon = &zone.FaceCommonArray;
    }
    void ScalarHeadBase::Set_bFaceCommon_0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b_FaceCommon->at(i1) = 0;
        }
    }
    int ScalarHeadBase::GetZoneID()
    {
        return Zone->ID;
    }
    bool ScalarHeadBase::GetIsInitialized()
    {
        return IsInitialized;
    }

    void ScalarHeadBase::SetIsInitialized(bool isInitialized) 
    {
        IsInitialized = isInitialized;
    }

}