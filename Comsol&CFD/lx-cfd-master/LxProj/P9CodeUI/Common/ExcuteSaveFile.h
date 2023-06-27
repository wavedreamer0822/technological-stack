#pragma once
#include <string>
#include <vector>
#include "ExcuteBase.h"
#include "ScalarTypes.h"
namespace LxCFD
{
    class ExcuteSaveFile : public ExcuteBase
    {
    public:
        std::string FilePath;
        std::vector<ScalarTypes> ExportScalars;
        virtual void Excute() override;
    };
}