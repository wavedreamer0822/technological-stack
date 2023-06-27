#pragma once
#include "Vector3d.h"
#include "FvFace.h"
#include "LxTool.h"
namespace LxCFD
{
    struct PhysicalFaceMinCorrect
    {
    public:
        Vector3d Normal;
        double gDiff;
        virtual void SetFace(FvFace &face, Vector3d &Df)
        {
            Normal = Vector3d::XXYYZZProduct(face.Normal, Df);
            gDiff = Vector3d::DotProduct(Normal, face.OToN) / LxTool::Pow2(face.OToNLength);
        }

        double CalNonOrthogonalityCorrection_inner(FvFace &face, std::vector<Vector3d> &gradPhi, std::vector<double> &x)
        {
            return calNonOrthogonalityCorrection(face, face.CalAverage(gradPhi), x);
        }
        double CalNonOrthogonalityCorrection_bound(FvFace &face, std::vector<Vector3d> &gradPhi, std::vector<double> &x)
        {
            return calNonOrthogonalityCorrection(face, gradPhi.at(face.OSideCell), x);
        }

    protected:
        virtual double calNonOrthogonalityCorrection(FvFace &face, const Vector3d &aveGrad, const std::vector<double> &phi)
        {
            return Vector3d::DotProduct(aveGrad, Normal - gDiff * face.OToN);
        }
    };
}