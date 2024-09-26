#include "tcpcontroler.h"
#include "../utility/utility.h"
#include "../inetaddress/inetaddress.h"

TcpControler::TcpControler(int socket) : _socket(socket), _device(new IoDevice(socket)) {}

InetAddress TcpControler::getLocalAddress()
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    ERROR_CHECK(::getsockname(_socket, (struct sockaddr *)&addr, &addr_len) == -1, "getLocalAddress error");
    return addr;
}

void TcpControler::setSocketOption(int option)
{
    for (int i = 0; i < socketoption::ENDOFSOCKETPOPTION; i++)
    {
        switch (i & option)
        {
        case socketoption::REUSEDADDRESS:
            setReusedAddress();
            break;
        case socketoption::REUSEDPORT:
            setReusedPort();
            break;
        case socketoption::NONEBLOCKSOCKET:
            setNoneBlcokSocket();
            break;
        default:
            break;
        }
    }
}

int TcpControler::recv(std::string &buf, int size)
{
    if (size == 0)
        return _device->recv(buf);
    return _device->boundary_recv(buf);
}

int TcpControler::send(std::string &buf, int size)
{
    if (size == 0)
        return _device->send(buf);
    return _device->boundary_send(buf);
}

void TcpControler::setReusedAddress()
{
    int flag = 1;
    int ret = ::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ERROR_CHECK(ret == -1, "set address reused falied");
}

void TcpControler::setReusedPort()
{
    int flag = 1;
    int ret = ::setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag));
    ERROR_CHECK(ret == -1, "set port reused falied");
}

void TcpControler::setNoneBlcokSocket()
{
    int flag = fcntl(_socket, F_GETFL, 0);
    ERROR_CHECK(flag == -1, "get socket flag failed which is -1");
    flag |= O_NONBLOCK;
    ERROR_CHECK(fcntl(_socket, F_SETFL, flag) == -1, "set socket noneblock falied");
}
