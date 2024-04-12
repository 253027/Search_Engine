#ifndef __READEVENTCHANNEL_HEAD_H__
#define __READEVENTCHANNEL_HEAD_H__

#include "channel.h"

class ReadEventChannel : public Channel
{
public:
    ReadEventChannel(std::shared_ptr<EventLoop> &loop, int fd) : Channel(loop, fd) {}

    inline virtual void CallBack() { _cb(); }

    inline virtual void setCallBack(std::function<void()> cb) { _cb = cb; }

private:
    std::function<void()> _cb;
};

#endif //__READEVENTCHANNEL_HEAD_H__