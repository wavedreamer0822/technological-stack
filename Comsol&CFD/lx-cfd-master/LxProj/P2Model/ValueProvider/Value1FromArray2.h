#pragma once
#include <vector>
#include "Value1Base.h"
namespace LxCFD
{
    template <typename T>
    class Value1FromArray2 : public Value1Base<T>
    {
    public:
        std::vector<T> *CellArray;
        std::vector<T> *FaceArray;
        void SetParameter(std::vector<T> *cellArray, std::vector<T> *faceArray)
        {
            CellArray = cellArray;
            FaceArray = faceArray;
        }
        virtual T GetCellValue(int cellIndex) override
        {
            return CellArray->at(cellIndex);
        }
        virtual T GetFaceValue(int faceIndex) override
        {
            return FaceArray->at(faceIndex);
        }
    };

}