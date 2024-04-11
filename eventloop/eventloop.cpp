#include "eventloop.h"
#include "../epoll/epoll.h"
#include "../channel/channel.h"
#include "../networkcontroler/tcpcontroler.h"

EventLoop::EventLoop(int server_sock) : _server_sock(server_sock), stop(false), _epoll(new Epoll()) {}

EventLoop::~EventLoop()
{
    for (auto &x : _connect_map)
        close(x.first);
}

void EventLoop::loop()
{
    while (!stop)
    {
        std::vector<Channel *> event = _epoll->epoll_wait();
        for (auto &x : event)
        {
            // 处理新客户端请连接
            if (x->getFileDescripter() == _server_sock && (x->getCalledEvent() & EPOLLIN))
                x->handleNewConnectionEvent();
            else // TCP连接读事件
                x->headleReadConnectionEvent();
        }
    }
}

void EventLoop::setStop()
{
    stop = true;
}

void EventLoop::updateChannel(Channel *ch)
{
    _epoll->updateChannel(ch);
}

void EventLoop::recordNewConnection(int fd, TcpControler *tcp)
{
    _connect_map[fd].reset(tcp);
}

void EventLoop::handleReadConnection(int client_sock)
{
    auto connection = _connect_map.find(client_sock);
    if (connection == _connect_map.end())
        return;
    printf("%s\n", "handle read events");
}
