#pragma once
#include "Value1FromArray1.h"
namespace LxCFD
{
    class Value1OppositeFromArray1
    {
    public:
        class Double : public Value1FromArray1<double>
        {

            virtual double GetCellValue(int cellIndex) override
            {
                return -CommonArray->at(cellIndex);
            }

            virtual double GetFaceValue(int faceIndex) override
            {
                return -CommonArray->at(faceIndex);
            }
        };
        class Vector : public Value1FromArray1<Vector3d>
        {
        public:
            Vector() {}
            Vector(std::vector<Vector3d> *array)
            {
                CommonArray = array;
            }
            virtual Vector3d GetCellValue(int cellIndex) override
            {
                return -CommonArray->at(cellIndex);
            }

            virtual Vector3d GetFaceValue(int faceIndex) override
            {
                return -CommonArray->at(faceIndex);
            }
        };
    };
}