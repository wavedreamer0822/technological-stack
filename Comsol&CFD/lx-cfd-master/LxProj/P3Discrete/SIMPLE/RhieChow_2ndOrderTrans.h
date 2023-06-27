#pragma once
#include "RhieChow_1stOrderTrans.h"
namespace LxCFD
{
    class RhieChow_2ndOrderTrans : public RhieChow_1stOrderTrans
    {
    public:
        std::vector<Vector3d> *RhoVel_oo;
        virtual Vector3d CalVelocityCorrection_Inner(int faceID, FvFace &face) override;
        virtual Vector3d CalVelocityCorrection_Bound(int faceID, FvFace &face) override;
    };
}