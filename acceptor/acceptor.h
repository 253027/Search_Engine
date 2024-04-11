#ifndef __ACCEPTOR_HEAD_H__
#define __ACCEPTOR_HEAD_H__

class EventLoop;
class Socket;
class Channel;

#include "../inetaddress/inetaddress.h"
#include "../socket/socket.h"
#include "../networkcontroler/tcpcontroler.h"
#include <memory>

class Acceptor
{
public:
    Acceptor(std::shared_ptr<EventLoop> &loop, std::shared_ptr<Socket> &socket);

private:
    void acceptNewConnection(std ::shared_ptr<EventLoop> loop, std::shared_ptr<Socket> socket);

    std::shared_ptr<EventLoop> _loop;

    std::shared_ptr<Socket> _socket;

    std::shared_ptr<Channel> _server_channel;
};

#endif //__ACCEPTOR_HEAD_H__