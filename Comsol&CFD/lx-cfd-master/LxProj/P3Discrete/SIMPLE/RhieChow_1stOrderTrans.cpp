#include "RhieChow_1stOrderTrans.h"

namespace LxCFD
{
    Vector3d RhieChow_1stOrderTrans::CalVelocityCorrection_Inner(int faceID, FvFace &face)
    {
        return Vel_o->at(faceID) = Vector3d::XXYYZZProduct(
                   face.CalAverage(*Dc),
                   -face.CalCFGradCorrection_inner(*PressureGrad, *Pressure) + TransientDataBase::Factor_Phi_1stOrder * RhoVel_o->at(faceID));
    }
    Vector3d RhieChow_1stOrderTrans::CalVelocityCorrection_Bound(int faceID, FvFace &face)
    {
        return Vel_o->at(faceID) = Vector3d::XXYYZZProduct(
                   Dc->at(face.OSideCell),
                   -face.CalCFGradCorrection_bound(*PressureGrad, *Pressure) + TransientDataBase::Factor_Phi_1stOrder * RhoVel_o->at(faceID));
    }
}