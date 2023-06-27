#pragma once
#include "Value1Base.h"

namespace LxCFD
{
    template <typename T>
    class Value1FromArray1 : public Value1Base<T>
    {
    public:
        std::vector<T> *CommonArray= nullptr;
        void SetParameter(std::vector<T> *array)
        {
            this->CommonArray = array;
        }
        virtual T GetCellValue(int cellIndex) override
        {
            return CommonArray->at(cellIndex);
        }
        virtual T GetFaceValue(int faceIndex) override
        {
            return CommonArray->at(faceIndex);
        }
    };
}