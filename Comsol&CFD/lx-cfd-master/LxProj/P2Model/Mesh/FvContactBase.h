#pragma once
#include <vector>
#include <memory>
#include "HeadBase.h"
#include "IndexNumber.h"
#include "FvPair.h"
#include "FvCell.h"
#include "FvFace.h"
#include "IProvideContactTopology.h"
#include "FvZone.h"
#include "AMGInContact.h"
#include "IPrepareMesh.h"
namespace LxCFD
{
    class FvContactBase : public HeadBase, public IProvideContactTopology, public IPrepareMesh
    {
    public:
        //local
        bool IsEnabled = true;
        bool IsConode = true;
        IndexNumber InnerIndex;
        std::vector<FvPair> Pairs;
        AMGInContact AMGSolver;
        ShortArray::Deep ShallowArrayStorage;
        //not local
        BiCGStabInZone *O_BiCGSolver;
        BiCGStabInZone *N_BiCGSolver;
        FvZone *OZone = nullptr;
        FvThread *OThread = nullptr;
        FvZone *NZone = nullptr;
        FvThread *NThread = nullptr;
        // region IProvideContactTopology
        virtual void PrepareMeshData() override;
        virtual ShortArray::Shallow &GetOZoneCellOFaces(int cellID) override;
        virtual ShortArray::Shallow &GetNZoneCellOFaces(int cellID) override;
        virtual IndexNumber &GetInnerIndex() override;
        // endregion
    };
}