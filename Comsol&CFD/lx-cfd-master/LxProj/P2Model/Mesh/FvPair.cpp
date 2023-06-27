#include "FvPair.h"

namespace LxCFD
{
    void FvPair::SetONIndex(int OFaceId, const FvFace &OFace, int NFaceId, const FvFace &NFace)
    {
        this->O_InnCell = OFace.OSideCell;
        this->O_Cell = OFace.NSideCell;
        this->O_Face = OFaceId;
        this->N_InnCell = NFace.OSideCell;
        this->N_Cell = NFace.NSideCell;
        this->N_Face = NFaceId;
    }
}