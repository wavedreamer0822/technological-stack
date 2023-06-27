#include "IndexRecorder.h"

namespace LxCFD
{
    IndexRecorder::IndexRecorder() {}
    IndexRecorder::  IndexRecorder(int start,int end) : Start(start), End(end) {}
    void IndexRecorder::GetSeg(int &out_tart, int &out_endPlus1, int segIndex)
    {
        int nodeCount = GetCount();
        int taskCount = MultiThreads::GetThreadsCount();
        out_tart = Start + nodeCount * segIndex / taskCount;
        out_endPlus1 = Start + nodeCount * (segIndex + 1) / taskCount;
    }
}