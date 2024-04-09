#ifndef __SOCKET_HEAD_H__
#define __SOCKET_HEAD_H__

#include <sys/socket.h>
#include <unistd.h>

class Socket
{
public:
    Socket();

    explicit Socket(int fd);

    ~Socket();

    int getFd() const;

private:
    int _socket_fd;
};

#endif //__SOCKET_HEAD_H__