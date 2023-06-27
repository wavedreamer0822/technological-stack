#pragma once
#include <vector>
#include <memory>
#include "IReset.h"
#include "ExcuteBase.h"
namespace LxCFD
{
    class ExcuteCenter : public IReset
    {
    public:
        std::vector<std::shared_ptr<ExcuteBase>> ExcuteAfterAll_Fixed;
        void Reset(ResetTypes resetType);
        void ExcuteBeforeStep();
        void ExcuteAfterStep();
        void ExcuteAfterAll();
    };
}