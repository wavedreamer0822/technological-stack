#include "ComputeState.h"

namespace LxCFD
{
    ComputeState::ComputeStateTypes ComputeState::_ComputeState = ComputeState::ComputeStateTypes::NotRunning;
    std::mutex ComputeState::_LocalMutex;
    volatile bool ComputeState::_SettingChanged = true;
    bool ComputeState::IsNeedInterrupt()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        return _ComputeState == ComputeStateTypes::Running_InterruptByUser || _ComputeState == ComputeStateTypes::Running_InterruptByError;
    }
    bool ComputeState::IsSettingChanged()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        return _SettingChanged;
    }
    void ComputeState::ReportSettingChanged()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        if (!_SettingChanged)
        {
            _SettingChanged = true;
        }
    }
    void ComputeState::ReportSettingNoticed()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        if (_SettingChanged)
        {
            _SettingChanged = false;
        }
    }
    bool ComputeState::GetIsRunning()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        return _ComputeState != ComputeStateTypes::NotRunning;
    }
    bool ComputeState::SetIsRunning(bool isRunning)
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        if (isRunning)
        {
            if (_ComputeState != ComputeStateTypes::NotRunning)
                return false;
            _ComputeState = ComputeStateTypes::Running;
        }
        else
        {
            _ComputeState = ComputeStateTypes::NotRunning;
        }
        return true;
    }
    void ComputeState::ReportInterrupt_ByUser()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        if (_ComputeState == ComputeStateTypes::Running)
        {
            _ComputeState = ComputeStateTypes::Running_InterruptByUser;
        }
    }
    void ComputeState::ReportInterrupt_FindError()
    {
        std::unique_lock<std::mutex> lock(_LocalMutex);
        if (_ComputeState == ComputeStateTypes::Running)
        {
            _ComputeState = ComputeStateTypes::Running_InterruptByError;
        }
    }

}