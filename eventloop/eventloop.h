#ifndef __EVENTLOOP_HEAD_H__
#define __EVENTLOOP_HEAD_H__

class EventLoop
{
public:
    EventLoop();

    void loop();

    void setStop();

    ~EventLoop();

private:
    bool stop;
};

#endif __EVENTLOOP_HEAD_H__