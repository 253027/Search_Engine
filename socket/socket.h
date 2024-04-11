#ifndef __SOCKET_HEAD_H__
#define __SOCKET_HEAD_H__

#include <sys/socket.h>
#include <unistd.h>

class InetAddress;

class Socket
{
public:
    explicit Socket(int socket, int type = 0);

    ~Socket();

    void bind(const InetAddress &addr);

    void listen();

    int accept();

    int getFd() const;

private:
    int _socket_fd;
};

#endif //__SOCKET_HEAD_H__