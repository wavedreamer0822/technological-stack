#pragma once
#include "Value2Base.h"
#include "Value1Base.h"
#include "Vector3d.h"
namespace LxCFD
{
    class Value2List
    {
    public:
        template <typename T>
        class Base : public Value2Base<T>
        {
        public:
            std::vector<std::shared_ptr<Value1Base<T>>> Value1s;
            std::vector<std::shared_ptr<Value2Base<T>>> Value2s;
        };
        class Double : public Base<double>
        {
        public:
            virtual std::shared_ptr<Value2Base<double>> GetCopy(HeadBase *zoneOrContact) override;
            virtual void GetCellValue(double &out_S_Ad, double &out_S_b, int cellIndex) override;
            virtual void GetFaceValue(double &out_S_Ad, double &out_S_b, int faceIndex) override;
        };
        class Vector : public Base<Vector3d>
        {
        public:
            virtual std::shared_ptr<Value2Base<Vector3d>> GetCopy(HeadBase *zoneOrContact) override;
            virtual void GetCellValue(Vector3d &out_a, Vector3d &out_b, int cellIndex) override;
            virtual void GetFaceValue(Vector3d &out_a, Vector3d &out_b, int faceIndex) override;
        };
    };
}