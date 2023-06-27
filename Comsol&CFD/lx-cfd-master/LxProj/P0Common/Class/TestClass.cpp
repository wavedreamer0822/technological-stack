#include "TestClass.h"
#include <iostream>
namespace LxCFD
{
    TestClass::TestClass()
    {
        std::cout << "TestClass Created" << std::endl;
    }
    TestClass::~TestClass(){
          std::cout << "TestClass Released" << std::endl;
    }
}