#pragma once
#include "RhieChowInterpolation.h"
#include "TransientDataBase.h"
namespace LxCFD
{
    class RhieChow_1stOrderTrans : public RhieChowInterpolation
    {
    public:
        std::vector<Vector3d> *RhoVel_o;
        std::vector<Vector3d> *Vel_o;
        virtual Vector3d CalVelocityCorrection_Inner(int faceID, FvFace &face) override;
        virtual Vector3d CalVelocityCorrection_Bound(int faceID, FvFace &face) override;
    };
}