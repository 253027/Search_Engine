#ifndef __EVENTLOOP_HEAD_H__
#define __EVENTLOOP_HEAD_H__

#include <vector>
#include <memory>
#include <unistd.h>

class Epoll;
class Channel;
class TcpControler;

class EventLoop
{
public:
    EventLoop(TcpControler &tcp);

    void loop();

    void setStop();

private:
    bool stop;

    std::unique_ptr<Epoll> _epoll;

    std::unique_ptr<TcpControler> _tcp;
};

#endif //__EVENTLOOP_HEAD_H__