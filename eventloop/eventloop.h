#ifndef __EVENTLOOP_HEAD_H__
#define __EVENTLOOP_HEAD_H__

#include <vector>
#include <memory>
#include <unistd.h>
#include <unordered_map>

class Epoll;
class Channel;
class TcpControler;

class EventLoop
{
public:
    EventLoop();

    void loop();

    void setStop();

    void updateChannel(Channel *ch);

    void recordNewConnection(int fd, TcpControler *tcp);

private:
    bool stop;

    std::shared_ptr<Epoll> _epoll;

    std::unordered_map<int, std::shared_ptr<TcpControler>> _connect_map;
};

#endif //__EVENTLOOP_HEAD_H__