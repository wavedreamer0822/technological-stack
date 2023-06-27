#pragma once
#include "Value1Base.h"
#include "Vector3d.h"
namespace LxCFD
{
    class Value1List
    {
    public:
        template <typename T>
        class Base : public Value1Base<T>
        {
        public:
            std::vector<std::shared_ptr<Value1Base<T>>> Value1s;
        };
        class Double : public Base<double>
        {
        public:
            virtual double GetCellValue(int cellIndex) override;
            virtual double GetFaceValue(int faceIndex) override;
            virtual std::shared_ptr<Value1Base<double>> GetCopy(HeadBase *zoneOrContact) override;
        };
        class Vector : public Base<Vector3d>
        {
        public:
            virtual Vector3d GetCellValue(int cellIndex) override;
            virtual Vector3d GetFaceValue(int faceIndex) override;
            virtual std::shared_ptr<Value1Base<Vector3d>> GetCopy(HeadBase *zoneOrContact) override;
        };
    };
}