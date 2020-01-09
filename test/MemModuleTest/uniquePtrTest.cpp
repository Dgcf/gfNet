#include "../../src/base/Memory/inc/unique_ptr.h"
#include <iostream>
using namespace std;
using namespace gNet;

template<typename _T>
void judge(_T& t)
{
    if (t)
    {
        std::cout << "test3::io is not null" << std::endl;
    }
    else
    {
        std::cout << "test3::io is null" << std::endl;
    }
}

void test0()
{
    gNet::unique_ptr<int> i0(new int(12));
    std::cout << *i0 << std::endl;
}

void test1()
{
    gNet::unique_ptr<int> i0(new int(23));
    gNet::unique_ptr<int> i1(std::move(i0));
    std::cout << *i1 << std::endl;
    judge(i0);
}

void test2()
{
    gNet::unique_ptr<int> i0(new int(33));
    gNet::unique_ptr<int> i1(std::move(i0));
    int *i = i1.get();
    std::cout << *i << endl;
}

void test3()
{
    gNet::unique_ptr<int> i0(new int(43));
    i0.reset();
    
}

int main()
{
    // test0();
    // test1();
    // test2();
    test3();
}
