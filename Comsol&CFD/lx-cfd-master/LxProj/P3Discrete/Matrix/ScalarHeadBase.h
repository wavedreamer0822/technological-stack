#pragma once
#include <vector>
#include <cmath>
#include "IInitializable.h"
#include "IConnectivityAnalyzableZone.h"
#include "IndexNumber.h"
#include "FvFace.h"
#include "FvCell.h"
#include "Value1Base.h"
#include "Value2Base.h"
#include "ValueBase.h"
#include "ThreadsMath.h"
namespace LxCFD
{
    class FvZone;
    class ScalarHeadBase : public IInitializable, public IConnectivityAnalyzableZone
    {
    public:
        volatile bool IsInitialized = false;
        FvZone *Zone;
        std::vector<FvCell> *Cells;
        std::vector<FvFace> *Faces;
        IndexNumber *InnerIndex;
        IndexNumber *TotalIndex;
        std::vector<double> *x_Common;
        std::vector<double> *b_FaceCommon;
        virtual void CheckCreate(FvZone &zone);
        void Set_bFaceCommon_0(IndexNumber &indexNumber, int taskIndex);
        virtual int GetZoneID() override;
        virtual bool GetIsInitialized() override;
        virtual void SetIsInitialized(bool isInitialized) override;
  
    };
}