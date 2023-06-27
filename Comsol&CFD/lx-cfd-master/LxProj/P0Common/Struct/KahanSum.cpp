#include "KahanSum.h"
#include "LxTool.h"

namespace LxCFD
{
    void KahanSum::Add(double input)
    {
        double add = input - _LostPart;
        double temp = _Sum + add;
        _LostPart = (temp - _Sum) - add;
        _Sum = temp;
    }
    double KahanSum::GetSum()
    {
        double result = LxTool::RoundOff(_Sum, 12);
        _Sum = 0;
        _LostPart = 0;
        return result;
    }
}