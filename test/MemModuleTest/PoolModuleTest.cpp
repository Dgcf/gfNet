#include "../../src/base/Memory/inc/MemPool.h"
#include "../../src/common/common.h"
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

static gNet::pool<default_user_allocator> p(128, 32);


void Talloc()
{
    char* s0 = static_cast<char*>(p.malloc());
    strncpy(s0, vec_log[0], sizeof(*s0));
    printf("address is: %p, content is %s\n", s0, s0);
}

/****************************************************************
 * /home/gongfeng/study/code/C++/gfNet/src/base/Memory/inc
 * **************************************************************/
int main()
{
    for (int i = 0; i < 150; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Talloc();
    }
    
}
