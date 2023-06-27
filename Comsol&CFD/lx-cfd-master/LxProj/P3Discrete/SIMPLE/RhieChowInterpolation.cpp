#include "RhieChowInterpolation.h"
#include "PressureCorrectionBasic.h"
#include "PressureSIMPLE.h"
namespace LxCFD
{
    void RhieChowInterpolation::SetParameter(PressureCorrectionBasic *pressureCorInSIMPLE, PressureSIMPLE *pressureInSIMPLE)
    {
        Dc = pressureCorInSIMPLE->Dc.get();

        Pressure = pressureInSIMPLE->x.get();
        PressureGrad = pressureInSIMPLE->Grad.get();
    }
    Vector3d RhieChowInterpolation::CalVelocityCorrection_Inner(int faceID, FvFace &face)
    {
        return Vector3d::XXYYZZProduct(face.CalAverage(*Dc), -face.CalCFGradCorrection_inner(*PressureGrad, *Pressure)); //Dc改为不包含松弛的了，因此直接用公式
    }
    Vector3d RhieChowInterpolation::CalVelocityCorrection_Bound(int faceID, FvFace &face)
    {
        return Vector3d::XXYYZZProduct(Dc->at(face.OSideCell), -face.CalCFGradCorrection_bound(*PressureGrad, *Pressure));
    }
}