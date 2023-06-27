#pragma once

namespace LxCFD
{
    struct ONPair
    {
    public:
        ONPair();
        ONPair(int owner, int neighbor);
        int Owner = 0;
        int Neighbor = 0;
    };
}
