#include "eventloop.h"
#include "../epoll/epoll.h"
#include "../channel/channel.h"
#include "../networkcontroler/tcpcontroler.h"
#include "../utility/utility.h"

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
            x->CallBack();
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
    auto tcp = connection->second;
    std::string buf;
    int ret = tcp->recv(buf);
    ERROR_CHECK(ret == -1, "tcp read error which socket id is %d", client_sock);
    if (ret == 0)
    {
        close(client_sock);
        _connect_map.erase(connection);
    }
    printf("message from client %s\n", buf.c_str());
}
