#include "Value2List.h"

namespace LxCFD
{
    std::shared_ptr<Value2Base<double>> Value2List::Double::GetCopy(HeadBase *zoneOrContact)
    {
        std::shared_ptr<Double> copy;
        copy->Value1s.resize(Value1s.size());
        copy->Value2s.resize(Value2s.size());
        for (auto &l : Value1s)
        {
            copy->Value1s.push_back(l->GetCopy(zoneOrContact));
        }
        for (auto &l : Value2s)
        {
            copy->Value2s.push_back(l->GetCopy(zoneOrContact));
        }
        return copy;
    }
    void Value2List::Double::GetCellValue(double &out_S_Ad, double &out_S_b, int cellIndex)
    {
        out_S_Ad = 0;
        out_S_b = 0;
        for (auto &v : Value1s)
        {
            out_S_b += v->GetCellValue(cellIndex);
        }
        for (auto &v : Value2s)
        {
            double sa, sb;
            v->GetCellValue(sa, sb, cellIndex);
            out_S_Ad += sa;
            out_S_b += sb;
        }
    }
    void Value2List::Double::GetFaceValue(double &out_S_Ad, double &out_S_b, int faceIndex)
    {
        out_S_Ad = 0;
        out_S_b = 0;
        for (auto &v : Value1s)
        {
            out_S_b += v->GetFaceValue(faceIndex);
        }
        for (auto &v : Value2s)
        {
            double sa, sb;
            v->GetFaceValue(sa, sb, faceIndex);
            out_S_Ad += sa;
            out_S_b += sb;
        }
    }
    std::shared_ptr<Value2Base<Vector3d>> Value2List::Vector::GetCopy(HeadBase *zoneOrContact)
    {
        std::shared_ptr<Vector> copy;
        copy->Value1s.resize(Value1s.size());
        copy->Value2s.resize(Value2s.size());
        for (auto &l : Value1s)
        {
            copy->Value1s.push_back(l->GetCopy(zoneOrContact));
        }
        for (auto &l : Value2s)
        {
            copy->Value2s.push_back(l->GetCopy(zoneOrContact));
        }
        return copy;
    }
    void Value2List::Vector::GetCellValue(Vector3d &out_a, Vector3d &out_b, int cellIndex)
    {
        out_a = Vector3d();
        out_b = Vector3d();
        for (auto &v : Value1s)
        {
            out_b += (v->GetCellValue(cellIndex));
        }
        for (auto &v : Value2s)
        {
            Vector3d a, b;
            v->GetCellValue(a, b, cellIndex);
            out_a += (a);
            out_b += (b);
        }
    }
    void Value2List::Vector::GetFaceValue(Vector3d &out_a, Vector3d &out_b, int faceIndex)
    {
        out_a = Vector3d();
        out_b = Vector3d();
        for (auto &v : Value1s)
        {
            out_b += (v->GetFaceValue(faceIndex));
        }
        for (auto &v : Value2s)
        {
            Vector3d a, b;
            v->GetFaceValue(a, b, faceIndex);
            out_a += (a);
            out_b += (b);
        }
    }
}