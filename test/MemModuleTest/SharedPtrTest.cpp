#include "../../src/base/Memory/inc/shared_ptr.h"
#include <string>
#include <memory>
using namespace std;
using namespace gNet;

// 测试申请各种内建类型
void test1()
{
    gNet::shared_ptr<int> p1(new int(12));
    gNet::shared_ptr<char> p2(new char('b'));
    gNet::shared_ptr<double> p3(new double(44.4));
    gNet::shared_ptr<string> p4(new string("hello, world"));
}

// 测试拷贝构造, 赋值运算符
void test2()
{
    gNet::shared_ptr<int> p1(new int(22));
    gNet::shared_ptr<int> p2(p1);
    gNet::shared_ptr<int> p3(p2);
    gNet::shared_ptr<int> p4(p3);
    gNet::shared_ptr<int> p5(new int(33));
    gNet::shared_ptr<int> p6(p5);
    gNet::shared_ptr<int> p7 = p2;
    p1 = p6;
    p3 = p6;
    p4 = p3;
    gNet::shared_ptr<int> p8;
    p4 = p8;
}

// 测试取值
void test3()
{
    gNet::shared_ptr<int> p1(new int(22));
    gNet::shared_ptr<int> p2(p1);
    gNet::shared_ptr<int> p3(p2);
    std::cout << "p1: " << *p1 << "\n";
    std::cout << "p2: " << *p2 << "\n";
    std::cout << "p3: " << *p3 << "\n";
    // 测试operator-> TODO
}

// 测试operator bool/ use_count/ unique
void test4()
{
    gNet::shared_ptr<int> p1(new int(22));
    gNet::shared_ptr<int> p2(p1);
    gNet::shared_ptr<int> p3(p2);
    int a0 = p1?1:0;
    int a1 = p3?1:0;
    int a2 = p2.unique()?1:0;
    std::cout << a0 << "\t" << a1 << "\t" << a2 << std::endl;
    std::cout << p3.use_count() << std::endl;
}

/*********************************************************
 * dir /home/gongfeng/study/code/C++/gfNet/src/base/Memory/inc
 * *******************************************************/
int main()
{
    //test1();
    // test2();
    // test3();
    test4();
    std::unique_ptr<int> u;
    std::weak_ptr<int> w;
}
