#pragma once
#include <vector>
#include "GroupBase.h"
#include "IInitializable.h"

namespace LxCFD
{
    class InitializationGroup : public GroupBase
    {
    public:
        std::vector<IInitializable *> Initialization_Normal6;
        std::vector<IInitializable *> Initialization_Normal7;//例如vector初始化，需要等pressure初始化后
        std::vector<IInitializable *> Initialization_Transient9;
        virtual void Clear() override;
        void Initialize(bool isForce);

    protected:
        void initialize(bool isForce, std::vector<IInitializable *> &iniGroup);
    };
}