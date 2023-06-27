#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
#include "HeadBase.h"
namespace LxCFD
{
    template <typename T>
    class Value1Base;
    template <typename T>
    class Value2Base;
    template <typename T>
    class ValueBase
    {
    public:
        virtual ~ValueBase() = default;
        std::shared_ptr<ValueBase<T>> GetACopy(HeadBase *zoneOrContact)
        {
            if (Value1Base<T> *v1 = dynamic_cast<Value1Base<T> *>(this))
            {
                return v1->GetCopy(zoneOrContact);
            }
            else if (Value2Base<T> *v2 = dynamic_cast<Value2Base<T> *>(this))
            {
                return v2->GetCopy(zoneOrContact);
            }
            else
            {
                throw std::invalid_argument("Unexpected type");
            }
        }
    };
}