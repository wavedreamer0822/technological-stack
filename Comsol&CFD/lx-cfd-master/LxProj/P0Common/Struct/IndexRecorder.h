#pragma once
#include "MultiThreads.h"

namespace LxCFD
{
    struct IndexRecorder
    {
    public:
        IndexRecorder();
        IndexRecorder(int start, int end);
        int Start = 0;
        int End = 0;
        void GetSeg(int &out_tart, int &out_endPlus1, int segIndex);
        inline int GetCount() { return End - Start + 1; }
    };
}