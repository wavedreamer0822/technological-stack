#pragma once
#include "ShortArray.h"
#include "IndexNumber.h"
namespace LxCFD
{
    class IProvideContactTopology
    {
    public:
        virtual ShortArray::Shallow &GetOZoneCellOFaces(int cellID) = 0;
        virtual ShortArray::Shallow &GetNZoneCellOFaces(int cellID) = 0;
        virtual IndexNumber &GetInnerIndex() = 0;
    };
}