#include "socket.h"
#include "../utility/utility.h"

Socket::Socket() : _socket_fd(-1)
{
    _socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(_socket_fd == -1, "create socket failed");
}

Socket::Socket(int fd) : _socket_fd(-1)
{
    if (fd == -1)
    {
        ERROR_CHECK(fd == -1, "error value fd, which is -1");
        return;
    }
    _socket_fd = fd;
}

Socket::~Socket()
{
    if (_socket_fd != -1)
    {
        ::close(_socket_fd);
    }
}

int Socket::getFd() const
{
    return _socket_fd;
}
