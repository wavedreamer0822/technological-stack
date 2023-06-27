#include "AMGInZone.h"

namespace LxCFD
{
    void AMGInZone::Create(MGMeshCreator &commonData, IProvideZoneTopology *startZone, int startZoneCellLength, std::vector<double> *zoneCellCommonArray)
    {
        //创建多重网格
        MGZoneCreator &zoneCreator = commonData.zoneCreator;
        // if ((int)zoneCreator.InCoarseCell.size() < startZoneCellLength)
        // {
        //     zoneCreator.InCoarseCell.resize(startZoneCellLength);
        // }
        MgZones.clear();
        std::unique_ptr<MGZone> mgzone = zoneCreator.CreateMGZone(startZone);
        MgZones.push_back(std::move(mgzone));
        MaxCoarseLevel = 0;
        while ((int)MgZones.size() < commonData.maxCoarseLevelLimit)
        {
            MGZone *fineZone = MgZones.back().get(); //[MgZones.Count - 1];
            std::unique_ptr<MGZone> coarseZone = zoneCreator.CreateMGZone(fineZone);
            if (fineZone->Cells.size() > coarseZone->Cells.size())
            {
                MaxCoarseLevel = MgZones.size();
            }
            MgZones.push_back(std::move(coarseZone));
        }
        //设置数组
        for (auto &cz : MgZones)
        {
            cz->CreateArray(this, zoneCellCommonArray);
        }
        for (std::size_t i1 = 1; i1 < MgZones.size(); ++i1)
        {
            MgZones.at(i1)->SetFinerZone(MgZones.at(i1 - 1).get());
        }
    }
    void AMGInZone::LinkToMatrix(IAMGSolvableZone *matrix)
    {
        MgZones.at(0)->SetFinerZone(matrix);
        matrix->GetBounds(e_FixValue, e_ALUO0, e_Couple);
        isNeededUpdateA = true;
    }

    void AMGInZone::Restrict(int taskIndex)
    {
        if (isNeededUpdateA)
        {
            MgZones.at(SolvingLevel)->Restrict_ArLUe(taskIndex);
        }
        else
        {
            MgZones.at(SolvingLevel)->Restrict_re(taskIndex);
        }
    }

    void AMGInZone::Prolong(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Prolong(taskIndex);
    }

    int AMGInZone::GetVariableCount()
    {
        return MgZones.at(0)->Cells.size();
    }

    void AMGInZone::CalResidual(int taskIndex)
    {
        MgZones.at(SolvingLevel)->CalResidual(taskIndex);
    }

    void AMGInZone::GetResidual_Reset(double &out_maxRc, double &out_maxacPhic)
    {
        out_maxRc = Max_Rc;
        out_maxacPhic = Max_acPhic;
        Max_Rc = 0;
        Max_acPhic = 0;
    }
    void AMGInZone::CalByJacobi_Step1(int taskIndex)
    {
        MgZones.at(SolvingLevel)->CalByJacobi_Step1(taskIndex);
    }

    void AMGInZone::CalByJacobi_Step2(int taskIndex)
    {
        MgZones.at(SolvingLevel)->CalByJacobi_Step2(taskIndex);
    }
    void AMGInZone::Cal_pArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_pArray(taskIndex);
    }

    void AMGInZone::Cal_rArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_rArray(taskIndex);
    }

    void AMGInZone::Cal_rhoPart1(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_rhoPart1(taskIndex);
    }

    void AMGInZone::Cal_sArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_sArray(taskIndex);
    }

    void AMGInZone::Cal_tArray_omega1(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_tArray_omega1(taskIndex);
    }

    void AMGInZone::Cal_vArray_alpha1(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_vArray_alpha1(taskIndex);
    }

    void AMGInZone::Cal_xArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_xArray(taskIndex);
    }

    void AMGInZone::Cal_yArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_yArray(taskIndex);
    }

    void AMGInZone::Cal_zArray(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Cal_zArray(taskIndex);
    }

    void AMGInZone::Initialize_Step1_r0rp1rho(int taskIndex)
    {
        MgZones.at(SolvingLevel)->Initialize_Step1_r0rp1rho(taskIndex);
    }
}