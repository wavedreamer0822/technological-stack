#pragma once
#include "FvThreadBase.h"
#include "MeshSelector.h"
#include "BoundaryTypes.h"
#include "WallThermalTypes.h"
#include "Value1Const.h"
namespace LxCFD
{
    class FvZone;
    class FvContact;
    class FvThread : public FvThreadBase, public MeshSelector
    {
    public:
        FvThread(FvZone *rootZone);
        FvZone *RootZone = nullptr;
        FvContact *RootContact = nullptr;
        BoundaryTypes BoundaryType;
        WallThermalTypes WallThermalType = WallThermalTypes::FixHeatFlux;
        std::unique_ptr<Value1Base<double>> Temperature = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(300));
        std::unique_ptr<Value1Base<double>> HeatFlux = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(0));
        std::unique_ptr<Value1Base<double>> Coupledh = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(10));
        std::unique_ptr<Value1Base<double>> CoupledT = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(300));
        bool IsNoSlipingWall = true;
        bool IsStaticWall = true;
        std::unique_ptr<Value1Base<Vector3d>> Velocity = std::unique_ptr<Value1Base<Vector3d>>(new Value1Const::Vector(Vector3d()));
        bool IsNormalToBound = true;
        std::unique_ptr<Value1Base<double>> VelocityMagnitude = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1));
        std::unique_ptr<Value1Base<double>> Pressure = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(0));
        bool GetIsCoupled();
    };
}