#pragma once
#include "MultiThreads.h"

namespace LxCFD
{
    class ValueStateLog
    {
    public:
        enum class ValueStates
        {
            RunOnce_Undone,
            RunOnce_Done,
            AlwaysRun,
        };
        ValueStateLog();
        ValueStateLog(bool isConst);
        volatile ValueStates ValueState = ValueStates::AlwaysRun;
        void SetState(bool isConst);
        void SetStateUsed();
        bool GetIsNeedToCal(int taskIndex);
    };
}