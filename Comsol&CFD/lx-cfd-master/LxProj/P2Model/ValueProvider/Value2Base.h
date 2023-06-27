#pragma once
#include "ValueBase.h"
#include "LxTool.h"
namespace LxCFD
{
    template <typename T>
    class Value2Base : public ValueBase<T>
    {
    public:
        virtual void GetCellValue(T &out_S_Ad, T &out_S_b, int cellIndex) { throw LxTool::GetNotImplementedException(); }
        virtual void GetFaceValue(T &out_S_Ad, T &out_S_b, int faceIndex) { throw LxTool::GetNotImplementedException(); }
        virtual std::shared_ptr<Value2Base<T>> GetCopy(HeadBase *zoneOrContact) = 0;
    };
}
