#include "Value1Const.h"

namespace LxCFD
{
    std::shared_ptr<Value1Const::Double> Value1Const::Double0 = std::shared_ptr<Value1Const::Double>(new Value1Const::Double(0));
    std::shared_ptr<Value1Const::Double> Value1Const::Double1 = std::shared_ptr<Value1Const::Double>(new Value1Const::Double(1));
    std::shared_ptr<Value1Const::Vector> Value1Const::Vector0 = std::shared_ptr<Value1Const::Vector>(new Value1Const::Vector(Vector3d(0, 0, 0)));      
}