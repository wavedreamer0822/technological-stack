#include "InitializationGroup.h"

namespace LxCFD
{
    void InitializationGroup::Clear()
    {
        Initialization_Normal6.clear();
        Initialization_Normal7.clear();
        Initialization_Transient9.clear();
    }
    void InitializationGroup::Initialize(bool isForce)
    {
        initialize(isForce, Initialization_Normal6);
        initialize(isForce, Initialization_Normal7);
        initialize(isForce, Initialization_Transient9);
    }
    void InitializationGroup::initialize(bool isForce, std::vector<IInitializable *> &iniGroup)
    {
        for (auto &ini : iniGroup)
        {
            if (isForce || !ini->GetIsInitialized())
            {
                ini->Initialize();
                ini->SetIsInitialized(true);
            }
        }
    }
}