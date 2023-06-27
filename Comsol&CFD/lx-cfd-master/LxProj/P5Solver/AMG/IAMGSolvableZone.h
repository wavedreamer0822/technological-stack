#pragma once
#include <vector>
#include "MGCell.h"
#include "MGFace.h"
namespace LxCFD
{
    class IAMGSolvableZone
    {
    public:
        virtual void Restrict_Ar(double &out_A, MGCell &mgCell) = 0;
        virtual void Restrict_r(MGCell &mgCell) = 0;
        virtual void Restrict_ALU(double &out_ALUO, double& out_ALUN, MGFace &mgFace) = 0;
        virtual std::vector<double> *GetProlongArray()=0;
        virtual void GetBounds(std::vector<int> *&out_e_FixValue, std::vector<int> *&out_e_ALUO0, std::vector<int> *&out_e_Couple)=0;
    };
}