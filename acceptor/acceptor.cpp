#include "acceptor.h"
#include "../eventloop/eventloop.h"
#include "../channel/channel.h"
#include "../utility/utility.h"

Acceptor::Acceptor(std::shared_ptr<EventLoop> &loop, std::shared_ptr<Socket> &socket) : _loop(loop), _socket(socket)
{
    _socket->listen();
    _server_channel.reset(new Channel(_loop.get(), _socket->getFd()));
    std::function<void()> cb = std::bind(&Acceptor::acceptNewConnection, this, _loop, _socket);
    _server_channel->setCallBack(cb);
    _server_channel->enableReading();
}

void Acceptor::acceptNewConnection(std::shared_ptr<EventLoop> loop, std::shared_ptr<Socket> socket)
{
    int client_sock = socket->accept();
    ERROR_CHECK(client_sock == -1, "new client connected error");
    Channel *ch = new Channel(&*loop.get(), client_sock);
    ch->enableReading();
    std::cout << InetAddress::getRemoteAddress(client_sock);
}
