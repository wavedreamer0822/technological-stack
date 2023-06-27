#include "ONPair.h"

namespace LxCFD
{
    ONPair::ONPair() {}
    ONPair::ONPair(int owner, int neighbor) : Owner(owner), Neighbor(neighbor) {}
}