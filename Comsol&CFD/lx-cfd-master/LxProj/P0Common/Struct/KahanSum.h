#pragma once

namespace LxCFD
{
    struct KahanSum
    {
    private:
        double _Sum = 0;
        double _LostPart = 0;

    public:
        void Add(double input);
        double GetSum();
    };
}