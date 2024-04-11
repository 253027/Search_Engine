#include "eventloop.h"
#include "../epoll/epoll.h"
#include "../channel/channel.h"
#include "../networkcontroler/tcpcontroler.h"
#include "../inetaddress/inetaddress.h"

extern void newConnection(TcpControler &tcp, Epoll &epoll);

EventLoop::EventLoop(TcpControler &tcp) : stop(false), _epoll(new Epoll())
{
    _tcp.reset(&tcp);
    Channel *ch = new Channel(_tcp->getSocket(), EPOLLIN);
    ch->setCallBack(std::bind(newConnection, *_tcp.get(), *_epoll.get()));
    _epoll->addFileDescripter(ch);
}

void EventLoop::loop()
{
    while (!stop)
    {
        std::vector<Channel *> event = _epoll->epoll_wait();
        for (auto &x : event)
        {
            // x->handleEvent();
            if ((x->getCalledEvent() & EPOLLIN) && x->getFileDescripter() == _tcp->getSocket())
            {
                std::cout << "新链接" << std::endl;
                int t = _tcp->accept();
            }
        }
    }
}

void EventLoop::setStop()
{
    stop = true;
}
