#pragma once
#include <string>
#include "ScalarTypes.h"
namespace LxCFD
{
    class EnumsToString
    {
    public:
        std::string ConvertToString(ScalarTypes scalarType)
        {
            switch (scalarType)
            {
            case ScalarTypes::Temperature:
                return "Temperature";
            case ScalarTypes::Pressure:
                return "Pressure";
            case ScalarTypes::PressureCorrection:
                return "PressureCorrection";
            case ScalarTypes::MassImbalance:
                return "MassImbalance";
            case ScalarTypes::Velocity:
                return "Velocity";
            case ScalarTypes::Vel_U:
                return "Vel_U";
            case ScalarTypes::Vel_V:
                return "Vel_V";
            case ScalarTypes::Vel_W:
                return "Vel_W";
            case ScalarTypes::Turb_k:
                return "Turb_k";
            case ScalarTypes::Turb_w:
                return "Turb_w";
            case ScalarTypes::WallDistance:
                return "WallDistance";

            default:
                return "Undefined";
            }
        }
    };
}