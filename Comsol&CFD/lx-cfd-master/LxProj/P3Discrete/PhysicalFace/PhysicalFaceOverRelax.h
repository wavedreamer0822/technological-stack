#pragma once
#include "PhysicalFaceOrthCorrect.h"
namespace LxCFD
{
    class PhysicalFaceOverRelax : public PhysicalFaceOrthCorrect
    {
    public:
        virtual void SetFace(FvFace &face, Vector3d &Df) override
        {
            Normal = Vector3d::XXYYZZProduct(face.Normal, Df);
            double normalDotOToN = Vector3d::DotProduct(Normal, face.OToN);
            gDiff = Normal.CalLengthSquared() / normalDotOToN;
            gT = normalDotOToN / LxTool::Pow2(face.OToNLength);
        }
    };
}