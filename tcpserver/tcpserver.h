#ifndef __TCPSERVER_HEAD_H__
#define __TCPSERVER_HEAD_H__

#include <memory>
#include <string>

class Socket;
class Acceptor;
class EventLoop;

class TcpServer
{
public:
    TcpServer(const std::string &ip, const uint16_t port);

    void start();

    void stop();

private:
    std::shared_ptr<Socket> _ser_sock;

    std::shared_ptr<EventLoop> _loop;

    std::shared_ptr<Acceptor> _ac;
};

#endif //__TCPSERVER_HEAD_H__