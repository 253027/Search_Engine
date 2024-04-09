#include "eventloop.h"

EventLoop::EventLoop() : stop(false)
{
    ;
}

void EventLoop::loop()
{
    while (!stop)
    {
        ;
    }
}

void EventLoop::setStop()
{
    stop = true;
}

EventLoop::~EventLoop()
{
    ;
}
