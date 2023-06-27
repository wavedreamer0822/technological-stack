#pragma once
#include "PhysicalFaceMinCorrect.h"
namespace LxCFD
{
    class PhysicalFaceOrthCorrect : public PhysicalFaceMinCorrect
    {
    public:
        double gT;
        virtual void SetFace(FvFace &face, Vector3d &Df) override
        {
            Normal = Vector3d::XXYYZZProduct(face.Normal, Df);
            gDiff = Normal.CalLength() / face.OToNLength;
            gT = Vector3d::DotProduct(Normal, face.OToN) / LxTool::Pow2(face.OToNLength);
        }

    protected:
        virtual double calNonOrthogonalityCorrection(FvFace &face, const Vector3d &aveGrad, const std::vector<double> &phi) override
        {
            return Vector3d::DotProduct(aveGrad, Normal - gT * face.OToN) + (phi.at(face.NSideCell) - phi.at(face.OSideCell)) * (gT - gDiff);
        }
    };
}