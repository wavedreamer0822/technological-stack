#include "GeomIntegralMonitor.h"

namespace LxCFD
{
    void GeomIntegralMonitor::CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex)
    {
        double sum = 0;
        auto &cells = selectedZone.Cells;
        int i1, endp1;
        selectedZone.InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            sum += scalarArray.at(i1) * cells.at(i1).Volumn;
        }
        ThreadsMath::AddToSum(sum);
    }
    void GeomIntegralMonitor::CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex)
    {
        double sum = 0;
        auto &faces = selectedZone.Faces;
        int i1, endp1;
        selectedThread.ThreadIndex.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = faces.at(i1);
            sum += scalarArray.at(face.NSideCell) * face.Area;
        }
        ThreadsMath::AddToSum(sum);
    }
}