#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>

using namespace std;

struct T
{
    int a;
    string s;

    bool operator<(const T& t)
    {
        return a<t.a;
    }
};

int main()
{
    T t1, t2, t3, t4, t5;
    t1.a = 10;
    t1.s = "10ge";
    t2.a = 6;
    t2.s = "6good";
    t3.a = 25;
    t3.s = "25sorry";
    t4.a = 2;
    t4.s = "2hello";
    t5.a = 15;
    t5.s = "15are";
    
    list<T> l{t1,t2,t3,t4,t5};
    cout << "before sore: \n";
    for (list<T>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << it->s << endl;
    }

    l.sort();

    cout << "after sort:\n";
    for (list<T>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << it->s << endl;
    }
    
    return 0;
}