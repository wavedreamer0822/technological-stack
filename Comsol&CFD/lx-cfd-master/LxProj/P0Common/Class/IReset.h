#pragma once

namespace LxCFD
{
    class IReset
    {
    public:
        enum class ResetTypes
        {
            ClearToLoadSimulation,
            ClearToLoadMesh,
            ClearFields,
            UpdateSolveCenter,
            None
        };
        virtual void Reset(ResetTypes resetType) = 0;
        // switch (resetType)
        // {
        // case ResetTypes::ClearToLoadSimulation:
        // case ResetTypes::ClearToLoadMesh:
        // case ResetTypes::ClearFields:
        // case ResetTypes::UpdateSolveCenter:
        // case ResetTypes::None:
        // default:
        // }
    };
}