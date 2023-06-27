#pragma once
#include "Value1Base.h"
#include "Vector3d.h"
namespace LxCFD
{
    class Value1Const
    {
    public:
        template <typename T>
        class Base : public Value1Base<T>
        {
        public:
            Base(T &number)
            {
                this->Number = number;
            }
            T Number;
            virtual T GetCellValue(int cellIndex)  override
            {
                return Number;
            }
            virtual T GetFaceValue(int faceIndex)  override
            {
                return Number;
            }
            virtual bool IsConstant()  override { return true; }
        };
        class Double : public Base<double>
        {
        public:
            Double(double number) : Base(number) {}
            virtual bool IsEqual0()  override
            {
                return Number == 0;
            }
            virtual std::shared_ptr<Value1Base<double>> GetCopy(HeadBase *zoneOrContact) override
            {
                return std::shared_ptr<Value1Base<double>>(new Double(Number));
            }
        };
        class Vector : public Base<Vector3d>
        {
        public:
            Vector(Vector3d number) : Base(number) {}
            virtual bool IsEqual0()  override
            {
                return Number.Is0();
            }
            virtual std::shared_ptr<Value1Base<Vector3d>> GetCopy(HeadBase *zoneOrContact) override
            {
                return std::shared_ptr<Value1Base<Vector3d>>(new Vector(Number));
            }
        };
        static std::shared_ptr<Double> Double0 ;
        static std::shared_ptr<Double> Double1 ;
        static std::shared_ptr<Vector> Vector0 ;
    };
}