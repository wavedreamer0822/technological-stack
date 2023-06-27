#include "ConnectHeadBase.h"
#include "FvContact.h"
namespace LxCFD
{
    void ConnectHeadBase::CheckCreate(FvContact &contact)
    {
        Contact = &contact;
        InnerIndex = &contact.InnerIndex;
        Pairs = &contact.Pairs;
        O_Cells = &contact.OZone->Cells;
        O_Faces = &contact.OZone->Faces;

 
        N_Cells = &contact.NZone->Cells;
        N_Faces = &contact.NZone->Faces;

        O_Index = &contact.OThread->ThreadIndex;
        N_Index = &contact.NThread->ThreadIndex;

        deltaOFaceId = O_Index->FaceIDs.Start;
        deltaOCellId = O_Index->CellIDs.Start;
        deltaNFaceId = N_Index->FaceIDs.Start;
        deltaNCellId = N_Index->CellIDs.Start;
    }
    void ConnectHeadBase::GetONZoneID(int &out_OZoneID, int &out_NZoneID)
    {
        out_OZoneID = Contact->OZone->ID;
        out_NZoneID = Contact->NZone->ID;
    }
}