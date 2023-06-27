#pragma once
#include "IConnectivityAnalyzableContact.h"
#include "FvPair.h"
#include "IndexNumber.h"
namespace LxCFD
{
    class FvContact;
    class ConnectHeadBase : public IConnectivityAnalyzableContact
    {
    public:
        FvContact *Contact;
        std::vector<FvPair> *Pairs;
        IndexNumber *InnerIndex;
        IndexNumber *O_Index;
        IndexNumber *N_Index;
        std::vector<FvCell> *O_Cells;
        std::vector<FvCell> *N_Cells;
        std::vector<FvFace> *O_Faces;
        std::vector<FvFace> *N_Faces;

        int deltaOFaceId;
        int deltaOCellId;
        int deltaNFaceId;
        int deltaNCellId;
        virtual void CheckCreate(FvContact &contact);
        void GetONZoneID(int &out_OZoneID, int &out_NZoneID);
    };
}