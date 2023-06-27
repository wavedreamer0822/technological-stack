#include "RhieChow_2ndOrderTrans.h"

namespace LxCFD
{
    Vector3d RhieChow_2ndOrderTrans::CalVelocityCorrection_Inner(int faceID, FvFace &face)
    {
        return Vel_o->at(faceID) = Vector3d::XXYYZZProduct(
                   face.CalAverage(*Dc),
                   -face.CalCFGradCorrection_inner(*PressureGrad, *Pressure) - TransientDataBase::Factor_PhiO_2ndOrder * RhoVel_o->at(faceID) - TransientDataBase::Factor_PhiOO_2ndOrder * RhoVel_oo->at(faceID));
    }
    Vector3d RhieChow_2ndOrderTrans::CalVelocityCorrection_Bound(int faceID, FvFace &face)
    {
        return Vel_o->at(faceID) = Vector3d::XXYYZZProduct(
                   Dc->at(face.OSideCell),
                   -face.CalCFGradCorrection_bound(*PressureGrad, *Pressure) - TransientDataBase::Factor_PhiO_2ndOrder * RhoVel_o->at(faceID) - TransientDataBase::Factor_PhiOO_2ndOrder * RhoVel_oo->at(faceID));
    }
}