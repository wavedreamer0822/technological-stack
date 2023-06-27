#pragma once
#include <vector>
#include <memory>
#include "Value1Base.h"
#include "Value2Base.h"
#include "Value1List.h"
#include "Value2List.h"

namespace LxCFD
{
    class ValueListMaker
    {
    public:
        template <typename T>
        class Base
        {
        public:
            std::vector<std::shared_ptr<Value1Base<T>>> Value1s;
            std::vector<std::shared_ptr<Value2Base<T>>> Value2s;
            void AddValueProvider(std::shared_ptr<ValueBase<T>> valueProvider)
            {
                if (std::shared_ptr<Value1Base<T>> value1 = std::dynamic_pointer_cast<Value1Base<T>>(valueProvider))
                {
                    AddValueProvider(value1);
                }
                else if (std::shared_ptr<Value2Base<T>> value2 = std::dynamic_pointer_cast<Value2Base<T>>(valueProvider))
                {
                    AddValueProvider(value2);
                }
                else
                {
                    throw std::invalid_argument("未定义的类型");
                }
            }
            void AddValueProvider(std::shared_ptr<Value1Base<T>> value1)
            {
                if (value1->IsEqual0())
                {
                }
                else if (std::shared_ptr<Value1List::Base<T>> vlist = std::dynamic_pointer_cast<Value1List::Base<T>>(value1))
                {
                    for (auto &l : vlist->Value1s)
                    {
                        Value1s.push_back(l);
                    }
                }
                else
                {
                    Value1s.push_back(value1);
                }
            }
            void AddValueProvider(std::shared_ptr<Value2Base<T>> value2)
            {
                if (std::shared_ptr<Value2List::Base<T>> vlist = std::dynamic_pointer_cast<Value2List::Base<T>>(value2))
                {
                    for (auto &l : vlist->Value1s)
                    {
                        Value1s.push_back(l);
                    }
                    for (auto &l : vlist->Value2s)
                    {
                        Value2s.push_back(l);
                    }
                }
                else
                {
                    Value2s.push_back(value2);
                }
            }
            virtual std::shared_ptr<Value1Base<T>> MakeValue1List() = 0;
            virtual std::shared_ptr<ValueBase<T>> MakeValueList() = 0;
        };
        class Double : public Base<double>
        {
        public:
            virtual std::shared_ptr<Value1Base<double>> MakeValue1List() override;
            virtual std::shared_ptr<ValueBase<double>> MakeValueList() override;
        };
        class Vector : public Base<Vector3d>
        {
        public:
            virtual std::shared_ptr<Value1Base<Vector3d>> MakeValue1List() override;
            virtual std::shared_ptr<ValueBase<Vector3d>> MakeValueList() override;
        };
    };
}