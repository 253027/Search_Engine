#include "./networkcontroler/tcpcontroler.h"
#include "./channel/channel.h"
#include "./eventloop/eventloop.h"
#include "./epoll/epoll.h"
#include "./inetaddress/inetaddress.h"
#include <iostream>

void handleReadEvent()
{
    ;
}

void newConnection(TcpControler &tcp, Epoll &epoll)
{
    // Channel *ch = new Channel(tcp.accept(), EPOLLIN | EPOLLET);
    // std::cout << ch->getFileDescripter() << __LINE__ << std::endl;
    // ch->setCallBack(std::bind(handleReadEvent));
    // epoll.addFileDescripter(ch);
    // std::cout << InetAddress::getRemoteAddress(ch->getFileDescripter());
}

int main()
{
    // using sockoptions = AbstractControl::socketoption;
    // TcpControler tcp("127.0.0.1", 9190);
    // tcp.setSocketOption(sockoptions::REUSEEDADDRESS | sockoptions::REUSEEDPORT);

    // EventLoop loop(tcp);
    // loop.loop();

    return 0;
}