#include "PhysicalCenter.h"
#include "LxConsole.h"
namespace LxCFD
{
    void PhysicalCenter::Remove(int index)
    {
        if (index >= 0 && index < (int)PhysicalModels.size())
        {
            if (PhysicalModels.at(index).use_count() > 1)
            {
                LxConsole::Warn("正在使用中，无法删除");
            }
            else
            {
                PhysicalModels.erase(PhysicalModels.begin() + index);
            }
        }
        else
        {
            LxConsole::Warn("索引值超出范围");
        }
    }
}