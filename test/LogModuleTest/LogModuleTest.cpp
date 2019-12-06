#include <stdio.h>
//#include "../../src/base/Log/inc/Logger.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/base/Log/inc/Logger.h"
#include "../../src/base/Thread/inc/ThreadPool.h"
#include <fstream>
using namespace gNet;

 vector<const char*> vec_log
{
    "1. To be both a speaker of words and a doer of deeds.",
    "2. Variety is the spice of life.",
    "3. Bad times make a good man.",
    "4. There is no royal road to learning.",
    "5. Doubt is the key to knowledge.",
    "6. The greatest test of courage on earth is to bear defeat without losing heart.",
    "7. A man's best friends are his ten fingers.",
    "8. Only they who fulfill their duties in everyday matters will fulfill them on great occasions.",
    "9. The shortest way to do many things is to only one thing at a time.",
    "10. Sow nothing, reap nothing.",
    "11. Life is real, life is earnest.",
    "12. Life would be too smooth if it had no rubs in it.",
    "13. Life is the art of drawing sufficient conclusions form insufficient premises.",
    "14. Life is fine and enjoyable, yet you must learn to enjoy your fine life.",
    "15. Life is but a hard and tortuous journey.",
    "16. Life is a horse, and either you ride it or it rides you.",
    "17. Life is a great big canvas, and you should throw all the paint on it you can.",
    "18. Life is like music. It must be composed by ear, feeling and instinct, not by rule.",
    "19. Life is painting a picture, not doing a sum.",
    "20. The wealth of the mind is the only wealth."
};

const char* logstr(const vector<const char*>& v)
{
    constexpr int size = 20;
    assert(size==v.size());

    gNet::RandomValue<0, size-1> r;
    unsigned int index = r();
    assert(index>=0 && index <20);
    return v[index];
}


/********************************************************************
 * 在log输出之前，先输出到文件中，和后续log文件做对比，是否有遗漏
 * ******************************************************************/
ofstream fs("./OriginLog.log", ofstream::app);      // 原始日志记录文件
std::mutex mx;
void OriginPrint(const char* s)
{
    std::lock_guard<std::mutex> lc(mx);
    fs << s << endl;
}

void test_info(void*)
{
    const char* s = logstr(vec_log);
    OriginPrint(s);
    LOG_INFO << s;
}

void test_debug(void*)
{
    const char* s = logstr(vec_log);
    OriginPrint(s);
    LOG_DEBUG << s;
}

void test_warning(void*)
{
    const char* s = logstr(vec_log);
    OriginPrint(s);
    LOG_WARNING << s;
}

void test_error(void*)
{
    const char* s = logstr(vec_log);
    OriginPrint(s);
    LOG_ERROR << s;
}

void test_fatal(void*)
{
    const char* s = logstr(vec_log);
    OriginPrint(s);
    LOG_FATAL << s;
}

void test(bool runing)
{
    int runningCount = 0;
    ThreadPool pool(10, nullptr);
    pool.start();

    MsgType<std::function<void(void*)>> ts[5];
    ts[0].priority_ = Last;
    ts[0].msg_ = test_info;

    ts[1].priority_ = Usual;
    ts[1].msg_ = test_debug;

    ts[2].priority_ = Mid;
    ts[2].msg_ = test_warning;

    ts[3].priority_ = High;
    ts[3].msg_ = test_error;

    ts[4].priority_ = Unknown;
    ts[4].msg_ = test_fatal;

    while (runing)
    {
        printf("Running Count: %d\n", ++runningCount);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        unsigned int index = gNet::RandomValue<0,4>()();
        pool.AddTask(ts[index]);
    }
}

/****************************************************************************
 * 调试目录：
 * dir /home/gongfeng/study/code/C++/gfNet/src/base/Log/src:/home/gongfeng/study/code/C++/gfNet/src/base/Thread/src:/home/gongfeng/study/code/C++/gfNet/src/base/Time/src
 * **************************************************************************/
int main()
{
    bool run = true;
    test(run);
    fs.close();
}
