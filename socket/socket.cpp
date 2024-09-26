#include "socket.h"
#include "../utility/utility.h"
#include "../inetaddress/inetaddress.h"

Socket::Socket(int socket, int type) : _socket_fd(-1)
{
    if (type)
    {
        _socket_fd = ::socket(AF_INET, socket, 0);
        ERROR_CHECK(_socket_fd == -1, "create socket failed");
    }
    else
    {
        if (socket == -1)
        {
            ERROR_CHECK(socket == -1, "error value fd, which is -1");
            return;
        }
        _socket_fd = socket;
    }
}

Socket::~Socket()
{
    if (_socket_fd != -1)
    {
        ::close(_socket_fd);
    }
}

void Socket::bind(const InetAddress &addr)
{
    int ret = ::bind(_socket_fd, (struct sockaddr *)(addr.getAddress()), sizeof(struct sockaddr));
    ERROR_CHECK(ret == -1, "socket bind error");
}

void Socket::listen()
{
    ERROR_CHECK(::listen(_socket_fd, SOMAXCONN) == -1, "socket listening error");
}

int Socket::accept()
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int ret = ::accept(_socket_fd, (struct sockaddr *)&addr, &addrlen);
    ERROR_CHECK(ret == -1, "socket accept error");
    return ret;
}

int Socket::getFd() const
{
    return _socket_fd;
}
