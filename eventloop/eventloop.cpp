#include "eventloop.h"
#include "../epoll/epoll.h"
#include "../channel/channel.h"

EventLoop::EventLoop() : stop(false), _epoll(new Epoll()) {}

void EventLoop::loop()
{
    while (!stop)
    {
        std::vector<Channel *> event = _epoll->epoll_wait();
        for (auto &x : event)
            x->handleEvent();
    }
}

void EventLoop::setStop()
{
    stop = true;
}

void EventLoop::updateChannel(Channel *ch)
{
    _epoll->updateChannel(ch);
    ch->setInEpoll();
}
