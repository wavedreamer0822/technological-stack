#include "ValueStateLog.h"

namespace LxCFD
{
    ValueStateLog::ValueStateLog()
    {
    }
    ValueStateLog::ValueStateLog(bool isConst)
    {
        SetState(isConst);
    }
    void ValueStateLog::SetState(bool isConst)
    {
        if (isConst)
        {
            ValueState = ValueStates::RunOnce_Undone;
        }
        else
        {
            ValueState = ValueStates::AlwaysRun;
        }
    }
    void ValueStateLog::SetStateUsed()
    {
        if (ValueState == ValueStates::RunOnce_Undone)
        {
            ValueState = ValueStates::RunOnce_Done;
        }
    }

    bool ValueStateLog::GetIsNeedToCal(int taskIndex)
    {
        switch (ValueState)
        {
        case ValueStates::RunOnce_Undone:
            MultiThreads::Sync(taskIndex, [this]()
                               { SetStateUsed(); });
            return true;
        case ValueStates::RunOnce_Done:
            return false;
        case ValueStates::AlwaysRun:
        default:
            return true;
        }
    }

}