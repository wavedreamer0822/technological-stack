#pragma once

namespace LxCFD
{
    enum class ConvectionSchemes
    {
        FirstOrderUpwind,
        SecondOrderUpwind,
        OSHER,
        OSHER_DC,
        MUSCL,
        MUSCL_DC
    };
}