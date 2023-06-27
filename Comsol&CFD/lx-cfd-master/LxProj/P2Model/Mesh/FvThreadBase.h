#pragma once
#include "HeadBase.h"
#include "IndexNumber.h"

namespace LxCFD
{
    class FvThreadBase : public HeadBase
    {
    public:
        double Area = 0;
        IndexNumber ThreadIndex;
    };
}