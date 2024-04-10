#include "eventloop.h"
#include "../epoll/epoll.h"
#include "../channel/channel.h"

EventLoop::EventLoop() : stop(false), _epoll(nullptr)
{
    _epoll = new Epoll();
}

void EventLoop::loop()
{
    while (!stop)
    {
        std::vector<Channel *> event = _epoll->epoll_wait();
        for (auto &x : event)
        {
            ;
        }
    }
}

void EventLoop::setStop()
{
    stop = true;
}

EventLoop::~EventLoop()
{
    if (_epoll)
    {
        delete _epoll;
        _epoll = nullptr;
    }
}
