#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <random>
#include <future>
#include <iostream>
#include "../../src/base/Thread/inc/blockqueue.h"
#include "../../src/base/Thread/inc/ThreadPool.h"
using namespace std;
using namespace gNet;

const static int g_threadnums = 20;
MsgQueue<string> msg;
std::atomic<int> all_num(0);

void task_1()
{
    string s = msg.get();
    printf("take_1 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(80));
}

void task_2()
{
    string s = msg.get();
    printf("take_2 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(60));
}

void task_3()
{
    string s = msg.get();
    printf("take_3 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(70));
}

void task_0()
{
    string s = msg.get();
    all_num.fetch_add(1);
    printf("task_0 msg is: %s\n", s.c_str());
}

void Add_msg1()
{
    vector<string> vec_msg = 
    {
        "hello", "Zsh", "is", "big", "God", "She", "Very", "Stronge", "But", "Also", "Study", "Hard", "So", "what", "are", "you", "Waiting", "for"
    };
    int size = vec_msg.size();
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, size-1);
    gNet::MsgType<string> msgtype;

    while (true)
    {
        int index = di(dre);
        printf("english index is: %d\n", index);
        msgtype.msg_ = vec_msg.at(index);
        msgtype.priority_ = Mid;
        msg.add(msgtype);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Add_msg2()
{
    vector<string> vec_msg = {
        "哈啰", "张", "是一位", "大", "神级别", "她是", "非常", "强大", "但是", "也照样", "学习", "努力地", "所以", "什么", "是在", "你", "等待", "为了"
    };
    int size = vec_msg.size();
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, size-1);
    gNet::MsgType<string> msgtype;

    while (true)
    {
        int index = di(dre);
        printf("chinese index is: %d\n", index);
        msgtype.msg_ = vec_msg.at(index);
        msgtype.priority_ = Mid;
        msg.add(msgtype);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

/************************************************
 * 1. 消息队列多线程添加消息
 * 2. 线程池多线程添加任务和执行
 * **********************************************/

void RunAdd(const string* s, const string tip)
{
    int size = strlen(s->c_str());
    printf("total size: %d\n", size);
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, size-1);
    gNet::MsgType<string> msgtype;

    while (true)
    {
        int index = di(dre);
        msgtype.msg_ = s[index];
        msgtype.priority_ = Mid;
        printf("%s is: %d, msg is: %s\n", tip.c_str(), index, msgtype.msg_.c_str());
        msg.add(msgtype);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void AddMsg()
{
    string s1[] = {"hello", "Zsh", "is", "big", "God", "She", "Very", "Stronge", "But", "Also", "Study", "Hard", "So", "what", "are", "you", "Waiting", "for"};
    string s2[] = { "哈啰", "慧总", "是一位", "大", "神级别", "她是", "非常", "强大", "但是", "也照样", "学习", "努力地", "所以", "什么", "是在", "你", "等待", "为了" };
    //vector<string*> vec_msg{s1, s2};
    
    std::future<void> result = std::async(std::launch::async, RunAdd, s2, "two");
    RunAdd(s1, "one");
    result.get();
}

void Test()
{
    gNet::ThreadPool pool(g_threadnums, nullptr);
    pool.start();
}

int main()
{
    //Test();
    AddMsg();

    return 0;
}
