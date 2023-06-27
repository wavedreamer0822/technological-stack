#include "AMGInContact.h"

namespace LxCFD
{
    void AMGInContact::Create(IProvideContactTopology *startContact, MGMeshCreator &commonData, AMGInZone &oZoneAMG, AMGInZone &nZoneAMG, int oThreadID, int nThreadID)
    {
        //网格
        MGContacts.clear();
        MGContactCreator &contactCreator = commonData.contactCreator;
        std::unique_ptr<MGContact> con = contactCreator.CreateMGContact(startContact,
                                                                        oZoneAMG.MgZones.at(0).get(), nZoneAMG.MgZones.at(0).get(),
                                                                        &oZoneAMG.MgZones.at(0)->ThreadIndexs.at(oThreadID),
                                                                        &nZoneAMG.MgZones.at(0)->ThreadIndexs.at(nThreadID));
        MGContacts.push_back(std::move(con));
        for (int i1 = 1; i1 < commonData.maxCoarseLevelLimit; ++i1)
        {
            std::unique_ptr<MGContact> c = contactCreator.CreateMGContact(MGContacts.at(i1 - 1).get(),
                                                                          oZoneAMG.MgZones.at(i1).get(), nZoneAMG.MgZones.at(i1).get(),
                                                                          &oZoneAMG.MgZones.at(i1)->ThreadIndexs.at(oThreadID),
                                                                          &nZoneAMG.MgZones.at(i1)->ThreadIndexs.at(nThreadID));
            MGContacts.push_back(std::move(c));
        }
        //设置数组
        MGContacts.at(0)->SetArray(this);
        for (std::size_t i1 = 1; i1 < MGContacts.size(); ++i1)
        {
            MGContacts.at(i1)->SetArray(this); // contact);
            MGContacts.at(i1)->SetFineContact(MGContacts.at(i1 - 1).get());
        }
    }
    void AMGInContact::LinkToMatrix(IAMGSolvableContact *connect)
    {
        MGContacts.at(0)->SetFineContact(connect);
        isNeededUpdateA = true;
    }
    void AMGInContact::Restrict(int taskIndex)
    {
        MGContacts.at(SolvingLevel)->Restrict_ALU(taskIndex);
    }
    void AMGInContact::Copy_xArray(int taskIndex)
    {
        MGContacts.at(SolvingLevel)->Copy_xArray(taskIndex);
    }
    void AMGInContact::Copy_xCommonArray(int taskIndex)
    {
        MGContacts.at(SolvingLevel)->Copy_xCommonArray(taskIndex);
    }
    void AMGInContact::Copy_yArray(int taskIndex)
    {
        MGContacts.at(SolvingLevel)->Copy_yArray(taskIndex);
    }
    void AMGInContact::Copy_zArray(int taskIndex)
    {
        MGContacts.at(SolvingLevel)->Copy_zArray(taskIndex);
    }
}