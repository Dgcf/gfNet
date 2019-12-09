#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <unistd.h>
#include <functional>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>

using namespace std;
using namespace placeholders;

#pragma region 
// struct T
// {
//     int a;
//     string s;

//     bool operator<(const T& t)
//     {
//         return a<t.a;
//     }
// };


// static char * get_local_time(char *time_str, int len, struct timeval *tv)
// {
//     struct tm* ptm;
//     char time_string[40];
//     long milliseconds;
    
//     ptm = localtime (&(tv->tv_sec));
 
//     /* 格式化日期和时间，精确到秒为单位。*/
//     //strftime (time_string, sizeof(time_string), "%Y/%m/%d %H:%M:%S", ptm); //输出格式为: 2018/12/09 10:48:31.391
//     //strftime (time_string, sizeof(time_string), "%Y|%m|%d %H-%M-%S", ptm); //输出格式为: 2018|12|09 10-52-28.302
//     //strftime (time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm); //输出格式为: 2018-12-09 10:52:57.200
//     strftime (time_string, sizeof(time_string), "%Y\\%m\\%d %H-%M-%S", ptm); //输出格式为: 2018\12\09 10-52-28.302
 
//     /* 从微秒计算毫秒。*/
//     milliseconds = tv->tv_usec / 1000;
 
//     /* 以秒为单位打印格式化后的时间日期，小数点后为毫秒。*/
//     snprintf (time_str, len, "%s.%03ld", time_string, milliseconds);
 
//     return time_str;
// }

// void* test1(void*s)
// {
//     printf("%s\n", (char*)s);
// }

// class A
// {
// public:
//     A(string s):s_(s){}
//     void say()
//     {
//         cout << s_ << ": hello, world" << endl;
//     }

//     void operator<<(const string& ss)
//     {
//         cout << ss << endl;
//     }

// private:
//     string s_;
// };

// #define PIR A("good")

// struct B
// {
//     string s;
//     B(): s("hahaha"){}

//     unsigned int operator()()
//     {
//         return s.size();
//     }
// };

// string stackTrace(bool demangle)
// {
//   string stack;
//   const int max_frames = 200;
//   void* frame[max_frames];
//   int nptrs = ::backtrace(frame, max_frames);
//   char** strings = ::backtrace_symbols(frame, nptrs);
//   if (strings)
//   {
//     size_t len = 256;
//     char* demangled = demangle ? static_cast<char*>(::malloc(len)) : nullptr;
//     for (int i = 1; i < nptrs; ++i)  // skipping the 0-th, which is this function
//     {
//       if (demangle)
//       {
//         // https://panthema.net/2008/0901-stacktrace-demangled/
//         // bin/exception_test(_ZN3Bar4testEv+0x79) [0x401909]
//         char* left_par = nullptr;
//         char* plus = nullptr;
//         for (char* p = strings[i]; *p; ++p)
//         {
//           if (*p == '(')
//             left_par = p;
//           else if (*p == '+')
//             plus = p;
//         }

//         if (left_par && plus)
//         {
//           *plus = '\0';
//           int status = 0;
//           char* ret = abi::__cxa_demangle(left_par+1, demangled, &len, &status);
//           *plus = '+';
//           if (status == 0)
//           {
//             demangled = ret;  // ret could be realloc()
//             stack.append(strings[i], left_par+1);
//             stack.append(demangled);
//             stack.append(plus);
//             stack.push_back('\n');
//             continue;
//           }
//         }
//       }
//       // Fallback to mangled names
//       stack.append(strings[i]);
//       stack.push_back('\n');
//     }
//     free(demangled);
//     free(strings);
//   }
//   return stack;
// }

// void test0()
// {
//     string s = stackTrace(true);
//     cout << s << endl;
// }
#pragma endregion

int a[32];
//(&arr)[32]
int (&arr)[32] = a;

class SourceFile
  {
   public:
    template<int N>
    SourceFile(const char (&arr)[N])          // 长度为N的char数组的引用
      : data_(arr),
        size_(N-1)
    {
      cout << "arr" << endl;
      const char* slash = strrchr(data_, '/'); // builtin function
      if (slash)
      {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr);
      }
    }

    explicit SourceFile(const char* filename)
      : data_(filename)
    {
      cout << "filename" << endl;
      const char* slash = strrchr(filename, '/');
      if (slash)
      {
        data_ = slash + 1;          // +1表示文件名开始的地址
      }
      size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  template <typename T>
T* CheckNotNull(SourceFile file, int line, const char *names, T* ptr)
{
  cout << "hello" << endl;
  return ptr;
}

#define CHECK_NOTNULL(val) CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", &val);

int main()
{
    // const char* s = "good";
    // ofstream of("./hello", ofstream::out|ofstream::app);
    // of<<s<<endl;
    int s = 11;
    // CHECK_NOTNULL(s)

    SourceFile fiel("hello");

    return 0;
}