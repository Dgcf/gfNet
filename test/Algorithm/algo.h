#include <algorithm>
#include <vector>
using namespace std;

void test0()
{
    vector<int> a;
    nth_element(a.begin(), a.end(), a.end(), a.begin());
}