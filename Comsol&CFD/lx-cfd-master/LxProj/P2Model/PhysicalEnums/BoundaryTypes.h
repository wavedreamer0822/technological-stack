#pragma once

namespace LxCFD
{
    enum class BoundaryTypes
    {
        Interior,
        SolidWall,
        FluidWall,
        VelocityInlet,
        PressureInOut,
        Symmetry,
    };
}