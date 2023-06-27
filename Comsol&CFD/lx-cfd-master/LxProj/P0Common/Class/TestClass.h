#pragma once
#include <memory>
namespace LxCFD
{
    class TestClass
    {
    public:
        TestClass();
        ~TestClass();
        int a = 9;
        //std::unique_ptr<int> b;
    };
}