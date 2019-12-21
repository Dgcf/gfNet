#include "../../src/base/Memory/inc/shared_ptr.h"
using namespace gNet;

// 测试申请各种类型
void test1()
{
    gNet::shared_ptr<int> p1(new int(12));
    // gNet::shared_ptr<char> p2(new char('b'));
    // gNet::shared_ptr<double> p3(new double(44.4));
}

// 测试拷贝
void test2()
{
    gNet::shared_ptr<int> p1(new int(22));
    gNet::shared_ptr<int> p2(p1);
    // gNet::shared_ptr<int> p3 = p2;
}

int main()
{
    test1();
}