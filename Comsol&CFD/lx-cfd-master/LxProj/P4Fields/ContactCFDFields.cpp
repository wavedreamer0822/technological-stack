#include "ContactCFDFields.h"
#include "FvContact.h"
#include "ConnectWallOneSide.h"
#include "ConnectWallTwoSide.h"
#include "AppRes.h"
namespace LxCFD
{
    void ContactCFDFields::SetParameter(FvContact *contact)
    {
        Contact = contact;
        bool advice = contact->IsEnabled;
        SetParameter_T(advice);
    }
    void ContactCFDFields::SetParameter_T(bool forwardAdvice)
    {
        int flag = 0;
        flag += Contact->OZone->PhysicalModel->IsEnergyEnabled;
        flag += Contact->NZone->PhysicalModel->IsEnergyEnabled;
        if (flag == 1)
        {
            throw std::invalid_argument("边界一侧未启用能量方程");
        }
        bool advice = forwardAdvice && flag == 2;
        if (advice)
        {
            if (Contact->Thickness->IsEqual0())
            {
                if (T == nullptr || !(dynamic_cast<ConnectWallOneSide *>(T.get())))
                {
                    T = std::unique_ptr<ConnectWallOneSide>(new ConnectWallOneSide());
                }
                ConnectWallOneSide *Ttemp = dynamic_cast<ConnectWallOneSide *>(T.get());
                Ttemp->CheckCreate(*Contact);
                Ttemp->setConnect(Contact->EnergySource->GetACopy(Contact), Contact->OZone->CFDFields.T.get(), Contact->NZone->CFDFields.T.get());
                AppRes::SolveCenter->TemperatureGroup.Connects.push_back(Ttemp);
            }
            else
            {
                if (T == nullptr || !(dynamic_cast<ConnectWallTwoSide *>(T.get())))
                {
                    T = std::unique_ptr<ConnectWallTwoSide>(new ConnectWallTwoSide());
                }
                ConnectWallTwoSide *Ttemp = dynamic_cast<ConnectWallTwoSide *>(T.get());
                Ttemp->CheckCreate(*Contact);
                Ttemp->setConnect(Contact->ThermalConductivity->GetCopy(Contact), Contact->Thickness->GetCopy(Contact),
                                  Contact->EnergySource->GetACopy(Contact), Contact->OZone->CFDFields.T.get(), Contact->NZone->CFDFields.T.get());
                AppRes::SolveCenter->TemperatureGroup.Connects.push_back(Ttemp);
            }
        }
        else
        {
            T = nullptr;
        }
    }
}