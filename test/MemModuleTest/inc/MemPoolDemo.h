#ifndef GNET_TEST_MEMPOOLDEMO_H
#define GNET_TEST_MEMPOOLDEMO_H

#include "../../../src/base/Memory/inc/MemPool.h"
#include "../../../src/common/common.h"
using namespace gNet;

class MemPool
{
public:
    MemPool(int size, int num);
    
private:
    gNet::pool<default_user_allocator> pool_;
};


#endif
