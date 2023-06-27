#pragma once

namespace LxCFD
{
    class IProvideVariableCount
    {
    public:
        virtual int GetVariableCount() = 0;
    };
}