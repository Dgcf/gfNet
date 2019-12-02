#include <stdio.h>
//#include "../../src/base/Log/inc/Logger.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/base/Log/inc/Logger.h"
#include "../../src/base/Thread/inc/ThreadPool.h"
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
    "14. Life is fine and enjoyable, yet you must learn to enjoy your fine life."
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

    gNet::RandomValue<0, size> r;
    unsigned int index = r();
    assert(index>=0 && index <20);
    return v[index];
}

void test_info(void*)
{
    LOG_INFO << logstr(vec_log);
}

void test_debug(void*)
{
    LOG_DEBUG << logstr(vec_log);
}

void test_warning(void*)
{
    LOG_WARNING << logstr(vec_log);
}

void test_error(void*)
{
    LOG_ERROR << logstr(vec_log);
}

void test_fatal(void*)
{
    LOG_FATAL << logstr(vec_log);
}

void test(bool runing)
{
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        unsigned int index = gNet::RandomValue<0,4>()();
        pool.AddTask(ts[index]);
    }
}

int main()
{
    bool run = true;
    test(run);
}
