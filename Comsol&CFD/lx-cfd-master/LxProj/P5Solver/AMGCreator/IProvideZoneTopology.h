#pragma once
#include <vector>
#include "IndexNumber.h"
#include "ShortArray.h"
namespace LxCFD
{
    class IProvideZoneTopology
    {
    public:
        virtual ShortArray::Shallow &GetCellOFaces(int cellID) = 0;
        virtual ShortArray::Shallow &GetCellNFaces(int cellID) = 0;
        virtual int GetFaceOSideCell(int faceID) = 0;
        virtual int GetFaceNSideCell(int faceID) = 0;
        virtual ONPair GetONCellID(int faceID) = 0;
        virtual IndexNumber &GetInnerIndex() = 0;
        virtual IndexNumber &GetTotalIndex() = 0;
        virtual int GetThreadCount() = 0;
        virtual IndexNumber &GetThreadIndex(int threadID) = 0;
    };
}