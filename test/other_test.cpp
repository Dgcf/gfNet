#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    char* sz = new char[32];
    strncpy(sz, "hello, world", 32);
    char* t = *(static_cast<char**>(static_cast<void*>(sz)));
    //printf("sz: %p, t: %p, t value is: %s\n", sz, t, *t);
    cout << t << endl;
    int a = 10;
}