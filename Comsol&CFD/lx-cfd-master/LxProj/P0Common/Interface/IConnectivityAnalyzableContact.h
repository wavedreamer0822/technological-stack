#pragma once
namespace LxCFD
{
    class IConnectivityAnalyzableContact
    {
        virtual void GetONZoneID(int &out_OZoneID, int &out_NZoneID) = 0;
    };
}
