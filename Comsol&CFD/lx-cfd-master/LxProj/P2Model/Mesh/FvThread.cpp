#include "FvThread.h"
#include "FvZone.h"
#include "FvContact.h"
namespace LxCFD
{
    FvThread::FvThread(FvZone *rootZone)
    {
        this->RootZone = rootZone;
    }
    bool FvThread::GetIsCoupled()
    {
        return RootContact != nullptr && RootContact->IsEnabled;
    }
}