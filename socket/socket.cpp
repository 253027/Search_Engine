#include "socket.h"

Socket::Socket() : _socket_fd(-1)
{
    _socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
}