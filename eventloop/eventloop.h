#ifndef __EVENTLOOP_HEAD_H__
#define __EVENTLOOP_HEAD_H__

#include <vector>

class Epoll;
class Channel;

class EventLoop
{
public:
    EventLoop();

    void loop();

    void setStop();

    ~EventLoop();

private:
    bool stop;

    Epoll *_epoll;
};

#endif //__EVENTLOOP_HEAD_H__