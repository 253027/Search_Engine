#ifndef __NEWCONCHANNEL_HEAD_H__
#define __NEWCONCHANNEL_HEAD_H__

#include "channel.h"

class NewConChanel : public Channel
{
public:
    inline NewConChanel(std::shared_ptr<EventLoop> &loop, int fd) : Channel(loop, fd) {}

    inline void setCallBack(std::function<void()> cb) override { _cb = cb; }

    inline void CallBack() override { _cb(); }

private:
    std::function<void()> _cb;
};

#endif //__NEWCONNECTIONCHANNEL_HEAD_H__