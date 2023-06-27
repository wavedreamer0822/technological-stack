#include "ValueListMaker.h"
#include "Value1Const.h"
namespace LxCFD
{
    std::shared_ptr<Value1Base<double>> ValueListMaker::Double::MakeValue1List()
    {
        if (Value1s.size() == 0)
        {
            return Value1Const::Double0;
        }
        else if (Value1s.size() == 1)
        {
            return Value1s.at(0);
            //return std::dynamic_pointer_cast<ValueBase<double>>(Value1s.at(0));
        }
        else
        {
            auto list = std::shared_ptr<Value1List::Double>(new Value1List::Double());
            list->Value1s = Value1s;
            return list;
        }
    }
    std::shared_ptr<ValueBase<double>> ValueListMaker::Double::MakeValueList()
    {
        if (Value2s.size() == 0)
        {
            return MakeValue1List();
        }
        else
        {
            if (Value2s.size() == 1 && Value1s.size() == 0)
            {
                return Value2s.at(0);
            }
            else
            {
                auto list = std::shared_ptr<Value2List::Double>(new Value2List::Double());
                list->Value1s = Value1s;
                list->Value2s = Value2s;
                return list;
            }
        }
    }
    std::shared_ptr<Value1Base<Vector3d>> ValueListMaker::Vector::MakeValue1List()
    {
        if (Value1s.size() == 0)
        {
            return Value1Const::Vector0;
        }
        else if (Value1s.size() == 1)
        {
            return Value1s.at(0);
        }
        else
        {
            auto list = std::shared_ptr<Value1List::Vector>(new Value1List::Vector());
            list->Value1s = Value1s;
            return list;
        }
    }
    std::shared_ptr<ValueBase<Vector3d>> ValueListMaker::Vector::MakeValueList()
    {
        if (Value2s.size() == 0)
        {
            return MakeValue1List();
        }
        else
        {
            if (Value2s.size() == 1 && Value1s.size() == 0)
            {
                return Value2s.at(0);
            }
            else
            {
                auto list = std::shared_ptr<Value2List::Vector>(new Value2List::Vector());
                list->Value1s = Value1s;
                list->Value2s = Value2s;
                return list;
            }
        }
    }

}