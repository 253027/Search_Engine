#include "tcpserver.h"
#include "../networkcontroler/tcpcontroler.h"
#include "../eventloop/eventloop.h"
#include "../acceptor/acceptor.h"

TcpServer::TcpServer(const std::string &ip, const uint16_t port)
{
    _ser_sock.reset(new Socket(SOCK_STREAM, 1));
    InetAddress address(ip, port);
    _ser_sock->bind(address);

    _loop.reset(new EventLoop(_ser_sock->getFd()));
    _ac.reset(new Acceptor(_loop, _ser_sock));
}

void TcpServer::start()
{
    _loop->loop();
}

void TcpServer::stop()
{
    _loop->setStop();
}
