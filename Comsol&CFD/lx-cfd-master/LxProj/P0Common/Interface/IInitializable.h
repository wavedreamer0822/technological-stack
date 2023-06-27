#pragma once
namespace LxCFD
{
    class IInitializable
    {
    public:
        virtual bool GetIsInitialized() = 0;
        virtual void SetIsInitialized(bool isInitialized) = 0;
        virtual void Initialize() = 0;
    };
}
