#include "tcpcontroler.h"
#include "../utility/utility.h"

TcpControler::TcpControler(const std::string &ip, int16_t port) : _address(new InetAddress(ip, port)),
                                                                  _socket(new Socket())
{
    _socket->bind(*_address);
    _socket->listen();
}

int TcpControler::accept()
{
    return _socket->accept();
}

InetAddress TcpControler::getLocalAddress()
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    ERROR_CHECK(::getsockname(_socket->getFd(), (struct sockaddr *)&addr, &addr_len) == -1, "getLocalAddress error");
    return addr;
}

InetAddress TcpControler::getRemoteAddress(int fd)
{
    return _address->getRemoteAddress(fd);
}
