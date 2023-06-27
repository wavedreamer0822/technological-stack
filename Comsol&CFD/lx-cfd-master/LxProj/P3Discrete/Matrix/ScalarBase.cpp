#include "ScalarBase.h"
#include "FvZone.h"
namespace LxCFD
{
    std::atomic<int> ScalarBase::UnnormalCount(0);
    std::atomic<int> ScalarBase::ExceedMaxCount(0);
    std::atomic<int> ScalarBase::ExceedMinCount(0);
    void ScalarBase::CheckCreate(FvZone &zone)
    {
        ScalarHeadBase::CheckCreate(zone);
        LxTool::CheckCreateVector(x, Cells->size());
        LxTool::CheckCreateVector(Grad, InnerIndex->CellIDs.GetCount());
    }
    void ScalarBase::CalGradient(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            Grad->at(i1) = Cells->at(i1).CalGradient_LeastSquare(*Faces, *x);
        }
    }
    void ScalarBase::set_x(Value1Base<double> &xValue, IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            x->at(i1) = xValue.GetCellValue(i1);
        }
    }
    void ScalarBase::CalBoundValue_grad0(FvFace &face) //更准确的做法见拉普拉斯方程中的设置，这样做结果没问题，因为收敛状态修正值为0，梯度修正也为0
    {
        Vector3d v = face.Normal - face.GetgT() * face.OToN;
        x->at(face.NSideCell) += ((x->at(face.OSideCell) - x->at(face.NSideCell)) * face.GetgT() - Vector3d::DotProduct(Grad->at(face.OSideCell), v)) / (face.GetgT() + Vector3d::DotProduct(face.Normal, v) / Cells->at(face.OSideCell).Volumn);
    }
    void ScalarBase::updateBound_grad0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            CalBoundValue_grad0(Faces->at(i1));
            //FvFace &face = Faces->at(i1);
            //x->at(face.NSideCell) = x->at(face.OSideCell);
        }
    }

    void ScalarBase::predict_bound_byCGrad(IndexNumber &indexNumber, int taskIndex) //方法1，精度一般，计算量小，对应P603
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FvFace &face = Faces->at(i1);
            x->at(face.NSideCell) = x->at(face.OSideCell) + Vector3d::DotProduct(Grad->at(face.OSideCell), face.OToN);
        }
    }
    void ScalarBase::SetLimitRule(bool isEnable, bool isLimMin, double minLim, bool isLimMax, double maxLim)
    {
        IsEnableLimit = isEnable;
        IsLimMin = isLimMin;
        MinLim = minLim;
        IsLimMax = isLimMax;
        MaxLim = maxLim;
    }
    void ScalarBase::Limit_x()
    {
        if (!IsEnableLimit)
            return;
        if (IsLimMin)
        {
            if (IsLimMax)
            {
                MultiThreads::RunCalTasks([this](int i)
                                          { limitMinMax(i); });
            }
            else
            {
                MultiThreads::RunCalTasks([this](int i)
                                          { limitMin(i); });
            }
        }
        else
        {
            if (IsLimMax)
            {
                MultiThreads::RunCalTasks([this](int i)
                                          { limitMax(i); });
            }
            else
            {
                MultiThreads::RunCalTasks([this](int i)
                                          { limitNaN(i); });
            }
        }
        if (UnnormalCount > 0)
        {
            std::stringstream ss;
            ss << "区域" << Zone->Name << "出现NAN值，数量" << UnnormalCount;
            LxConsole::Error(ss.str());
            ComputeState::ReportInterrupt_FindError();
            UnnormalCount = 0;
        }
        if (ExceedMaxCount > 0)
        {
            std::stringstream ss;
            ss << "区域" << Zone->Name << "中，" << ExceedMaxCount << "个网格超过上限" << MaxLim;
            LxConsole::Warn(ss.str());
            ExceedMaxCount = 0;
        }
        if (ExceedMinCount > 0)
        {
            std::stringstream ss;
            ss << "区域" << Zone->Name << "中，" << ExceedMinCount << "个网格超过下限" << MinLim;
            LxConsole::Warn(ss.str());
            ExceedMinCount = 0;
        }
    }
    void ScalarBase::limitNaN(int taskIndex)
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        int unnormal = 0;
        for (; i1 < endp1; ++i1)
        {
            double &xi = x->at(i1);
            if (std::isnan(xi))
            {
                unnormal++;
            }
        }
        UnnormalCount += unnormal;
    }

    void ScalarBase::limitMax(int taskIndex)
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        int exceedmax = 0;
        int unnormal = 0;
        for (; i1 < endp1; ++i1)
        {
            double &xi = x->at(i1);
            if (std::isnan(xi))
            {
                unnormal++;
            }
            else if (xi > MaxLim)
            {
                xi = MaxLim;
                exceedmax++;
            }
        }
        UnnormalCount += unnormal;
        ExceedMaxCount += exceedmax;
    }

    void ScalarBase::limitMin(int taskIndex)
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        int exceedmin = 0;
        int unnormal = 0;
        for (; i1 < endp1; ++i1)
        {
            double &xi = x->at(i1);
            if (std::isnan(xi))
            {
                unnormal++;
            }
            else if (xi < MinLim)
            {
                xi = MinLim;
                exceedmin++;
            }
        }
        UnnormalCount += unnormal;
        ExceedMinCount += exceedmin;
    }

    void ScalarBase::limitMinMax(int taskIndex)
    {
        int i1, endp1;
        TotalIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        int exceedmin = 0, exceedmax = 0;
        int unnormal = 0;
        for (; i1 < endp1; ++i1)
        {
            double &xi = x->at(i1);
            if (std::isnan(xi))
            {
                unnormal++;
            }
            else if (xi < MinLim)
            {
                xi = MinLim;
                exceedmin++;
            }
            else if (xi > MaxLim)
            {
                xi = MaxLim;
                exceedmax++;
            }
        }
        UnnormalCount += unnormal;
        ExceedMaxCount += exceedmax;
        ExceedMinCount += exceedmin;
    }

}