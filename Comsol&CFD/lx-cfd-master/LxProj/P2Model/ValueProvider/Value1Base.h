#pragma once
#include "ValueBase.h"
#include "LxTool.h"
namespace LxCFD
{
    template <typename T>
    class Value1Base : public ValueBase<T>
    {
    public:
        virtual T GetCellValue(int cellIndex) { throw LxTool::GetNotImplementedException(); }
        virtual T GetFaceValue(int faceIndex) { throw LxTool::GetNotImplementedException(); }
        virtual bool IsConstant() { return false; }
        virtual bool IsEqual0() { return false; }
        virtual std::shared_ptr<Value1Base<T>> GetCopy(HeadBase *zoneOrContact) { throw LxTool::GetNotImplementedException(); }
    };
}
