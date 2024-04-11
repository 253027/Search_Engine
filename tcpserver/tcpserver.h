#ifndef __TCPSERVER_HEAD_H__
#define __TCPSERVER_HEAD_H__

#include <memory>
#include <string>
#include <unordered_map>

class Socket;
class TcpControler;
class Acceptor;
class EventLoop;

class TcpServer
{
public:
    TcpServer(const std::string &ip, const uint16_t port);

    void start();

private:
    std::unordered_map<int, std::shared_ptr<TcpControler>> _connect_map;

    std::shared_ptr<Socket> _ser_sock;

    std::shared_ptr<EventLoop> _loop;

    std::shared_ptr<Acceptor> _ac;
};

#endif //__TCPSERVER_HEAD_H__