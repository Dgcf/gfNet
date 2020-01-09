#ifndef GFNET_FNETGT_IOMULTI_H_
#define GFNET_FNETGT_IOMULTI_H_

// #include "../../../common/common.h"
// #include <sys/epoll.h>
#include <memory>
#include <vector>
#include "./Channel.h"
#include "../../../base/Log/inc/Logger.h"


namespace gNet
{

namespace Fnetgt
{

class Channel;

class IOMultie
{
public:
    IOMultie();
    virtual ~IOMultie();

    //virtual void Poller(std::vector<std::unique_ptr<gNet::Fnetgt::Channel>>* __c);
    virtual void Poller(std::vector<Channel*>* __c) = 0;
    virtual void Update(uint32_t __e, uint32_t __t, void* _args) = 0;
};

} // namespace Fnetgt

} // namespace gNet

#endif
