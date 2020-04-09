#include "../../src/common/common.h"

void std_vector_test()
{
    std::vector<string> v1(10);
    // std::cout << v1.size() << "capacity:  " << v1.capacity() << std::endl;

    std::vector<string> v2(10, "hello");
    for(string& iter: v2)
    {
        std::cout << iter << endl;
    }
}

void std_vector_test2()
{
    std::vector<int> v1 = {1,2,3,4,5,6,7,8,9,0};
    allocator<int> alloc;
    auto p = alloc.allocate(v1.size() * 2);

    cout << typeid(p).name() << endl;
    auto q = uninitialized_copy(v1.begin(), v1.end(), p);
    uninitialized_fill_n(q, v1.size(), 42);

    for (size_t i = 0; i < 2*v1.size(); i++)
    {
        cout << *(p+i) << endl;
    }
    
}

int main()
{
    std_vector_test2();
}