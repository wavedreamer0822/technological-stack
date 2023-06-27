#include "Value1List.h"

namespace LxCFD
{
    double Value1List::Double::GetCellValue(int cellIndex)
    {
        double total = 0;
        for (auto &v : Value1s)
        {
            total += v->GetCellValue(cellIndex);
        }
        return total;
    }
    double Value1List::Double::GetFaceValue(int faceIndex)
    {
        double total = 0;
        for (auto &v : Value1s)
        {
            total += v->GetFaceValue(faceIndex);
        }
        return total;
    }
    std::shared_ptr<Value1Base<double>> Value1List::Double::GetCopy(HeadBase *zoneOrContact)
    {
        std::shared_ptr<Double> copy;
        copy->Value1s.resize(Value1s.size());
        for (auto &l : Value1s)
        {
            copy->Value1s.push_back(l->GetCopy(zoneOrContact));
        }
        return copy;
    }
    Vector3d Value1List::Vector::GetCellValue(int cellIndex)
    {
        Vector3d result;
        for (auto &v : Value1s)
        {
            result += (v->GetCellValue(cellIndex));
        }
        return result;
    }

    Vector3d Value1List::Vector::GetFaceValue(int faceIndex)
    {
        Vector3d result;
        for (auto &v : Value1s)
        {
            result += (v->GetFaceValue(faceIndex));
        }
        return result;
    }

    std::shared_ptr<Value1Base<Vector3d>> Value1List::Vector::GetCopy(HeadBase *zoneOrContact)
    {
        std::shared_ptr<Vector> copy;
        copy->Value1s.resize(Value1s.size());
        for (auto &l : Value1s)
        {
            copy->Value1s.push_back(l->GetCopy(zoneOrContact));
        }
        return copy;
    }
}