#pragma once

namespace LxCFD
{
    class IPrepareMesh
    {
        virtual void PrepareMeshData() = 0;
    };
}