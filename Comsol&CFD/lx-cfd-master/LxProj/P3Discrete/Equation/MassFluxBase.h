#pragma once
#include <memory>
#include "ScalarHeadBase.h"
namespace LxCFD
{
    class MassFluxBase : public ScalarHeadBase
    {
    public:
        std::shared_ptr<std::vector<double>> MassImbalance; //向外流出为正
        std::shared_ptr<std::vector<double>> MassFlux;
        std::shared_ptr<std::vector<float>> VelocityDirectionCorrection;
        virtual void CheckCreate(FvZone &zone) override
        {
            ScalarHeadBase::CheckCreate(zone);
            LxTool::CheckCreateVector(MassImbalance, Cells->size());
            LxTool::CheckCreateVector(MassFlux, Faces->size());
            LxTool::CheckCreateVector(VelocityDirectionCorrection, Faces->size());
        }
        virtual void CalFaceMassFlux(int taskIndex) = 0;
        virtual void CalMassImbalance(int taskIndex)
        {
            calMassImbanlance(*InnerIndex, taskIndex);
        }

    protected:
        void setFaceFlux_0(IndexNumber &indexNumber, int taskIndex)
        {
            int i1, endp1;
            indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
            for (; i1 < endp1; i1++)
            {
                MassFlux->at(i1) = 0;
            }
        }
        void calMassImbanlance(IndexNumber &indexNumber, int taskIndex)
        {
            int i1, endp1;
            indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
            for (; i1 < endp1; i1++)
            {
                MassImbalance->at(i1) = Cells->at(i1).CalIfOwnerAddElseMunus(*MassFlux);
            }
        }
        void setMassImbanlance_0(IndexNumber &indexNumber, int taskIndex)
        {
            int i1, endp1;
            indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
            for (; i1 < endp1; i1++)
            {
                MassImbalance->at(i1) = 0;
            }
        }
    };
}