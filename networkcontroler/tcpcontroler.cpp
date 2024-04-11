#include "tcpcontroler.h"
#include "../utility/utility.h"
#include "../inetaddress/inetaddress.h"

TcpControler::TcpControler(const std::string &ip, int16_t port) : _address(new InetAddress(ip, port)),
                                                                  _socket(new Socket(SOCK_STREAM, 1))
{
    _socket->bind(*_address);
    _socket->listen();
}

int TcpControler::accept()
{
    return _socket->accept();
}

int TcpControler::getSocket() const
{
    return _socket->getFd();
}

InetAddress TcpControler::getLocalAddress()
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    ERROR_CHECK(::getsockname(_socket->getFd(), (struct sockaddr *)&addr, &addr_len) == -1, "getLocalAddress error");
    return addr;
}

void TcpControler::setSocketOption(int option)
{
    for (int i = 0; i < socketoption::ENDOFSOCKETPOPTION; i++)
    {
        switch (i & option)
        {
        case socketoption::REUSEEDADDRESS:
            setReusedAddress();
            break;
        case socketoption::REUSEEDPORT:
            setReusedPort();
            break;
        default:
            break;
        }
    }
}

void TcpControler::setReusedAddress()
{
    int flag = 1;
    int ret = ::setsockopt(_socket->getFd(), SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ERROR_CHECK(ret == -1, "set address reused falied");
}

void TcpControler::setReusedPort()
{
    int flag = 1;
    int ret = ::setsockopt(_socket->getFd(), SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag));
    ERROR_CHECK(ret == -1, "set port reused falied");
}
