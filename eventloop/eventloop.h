#ifndef __EVENTLOOP_HEAD_H__
#define __EVENTLOOP_HEAD_H__

#include <vector>
#include <memory>
#include <unistd.h>

class Epoll;
class Channel;

class EventLoop
{
public:
    EventLoop();

    void loop();

    void setStop();

    void updateChannel(Channel *ch);

private:
    bool stop;

    std::shared_ptr<Epoll> _epoll;

    // std::unique_ptr<TcpControler> _tcp;
};

#endif //__EVENTLOOP_HEAD_H__