#pragma once
#include "IndexNumber.h"
#include "FvThreadBase.h"
#include "ValueStateLog.h"
namespace LxCFD
{
    class BoundaryHeadBase
    {
    public:
        IndexNumber *ThreadIndex;
        int ThreadID;
        void SetHead(FvThreadBase &thread)
        {
            ThreadIndex = &thread.ThreadIndex;
            ThreadID = thread.ID;
        }
    };
}