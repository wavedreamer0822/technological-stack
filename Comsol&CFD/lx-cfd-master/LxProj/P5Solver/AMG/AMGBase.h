#pragma once

namespace LxCFD
{
    class AMGBase
    {
    public:
        static int SolvingLevel;
        bool isNeededUpdateA = true;
    };
}