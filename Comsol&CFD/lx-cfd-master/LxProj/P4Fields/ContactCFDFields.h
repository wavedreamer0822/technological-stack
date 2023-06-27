#pragma once
#include "ConnectBase.h"
namespace LxCFD
{
    class FvContact;
    class ContactCFDFields
    {
    public:
        FvContact *Contact = nullptr;
        std::unique_ptr<ConnectBase> T;
        void SetParameter(FvContact *contact);
        void SetParameter_T(bool forwardAdvice);
    };
}