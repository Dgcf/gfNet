#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <unistd.h>
#include <functional>
#include <typeinfo>

using namespace std;
using namespace placeholders;

struct T
{
    int a;
    string s;

    bool operator<(const T& t)
    {
        return a<t.a;
    }
};


static char * get_local_time(char *time_str, int len, struct timeval *tv)
{
    struct tm* ptm;
    char time_string[40];
    long milliseconds;
    
    ptm = localtime (&(tv->tv_sec));
 
    /* 格式化日期和时间，精确到秒为单位。*/
    //strftime (time_string, sizeof(time_string), "%Y/%m/%d %H:%M:%S", ptm); //输出格式为: 2018/12/09 10:48:31.391
    //strftime (time_string, sizeof(time_string), "%Y|%m|%d %H-%M-%S", ptm); //输出格式为: 2018|12|09 10-52-28.302
    //strftime (time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm); //输出格式为: 2018-12-09 10:52:57.200
    strftime (time_string, sizeof(time_string), "%Y\\%m\\%d %H-%M-%S", ptm); //输出格式为: 2018\12\09 10-52-28.302
 
    /* 从微秒计算毫秒。*/
    milliseconds = tv->tv_usec / 1000;
 
    /* 以秒为单位打印格式化后的时间日期，小数点后为毫秒。*/
    snprintf (time_str, len, "%s.%03ld", time_string, milliseconds);
 
    return time_str;
}

void* test1(void*s)
{
    printf("%s\n", (char*)s);
}

int main()
{
    // T t1, t2, t3, t4, t5;
    // t1.a = 10;
    // t1.s = "10ge";
    // t2.a = 6;
    // t2.s = "6good";
    // t3.a = 25;
    // t3.s = "25sorry";
    // t4.a = 2;
    // t4.s = "2hello";
    // t5.a = 15;
    // t5.s = "15are";
    
    // list<T> l{t1,t2,t3,t4,t5};
    // cout << "before sore: \n";
    // for (list<T>::iterator it = l.begin(); it != l.end(); ++it)
    // {
    //     cout << it->s << endl;
    // }

    // l.sort();

    // cout << "after sort:\n";
    // for (list<T>::iterator it = l.begin(); it != l.end(); ++it)
    // {
    //     cout << it->s << endl;
    // }

    // char local_time_str[128];
    // char *p = NULL;
    // struct timeval tv;
 
    // gettimeofday(&tv, NULL);
    // p = get_local_time(local_time_str, sizeof(local_time_str), &tv);
    // printf("Get local time: \n%s\n", p);
    char s[12] = "hello";
    std::function<void*()> ty = std::bind(test1, s);
    ty();
    
    return 0;
}