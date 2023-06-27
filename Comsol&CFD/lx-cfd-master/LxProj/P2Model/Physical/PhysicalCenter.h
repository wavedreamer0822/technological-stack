#pragma once
#include <vector>
#include "PhysicalModel.h"

namespace LxCFD
{
    class PhysicalCenter
    {
    public:
        std::vector<std::shared_ptr<PhysicalModel>> PhysicalModels;
        void Remove(int index);
    };
}