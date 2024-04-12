#include "acceptor.h"
#include "../eventloop/eventloop.h"
#include "../channel/channel.h"
#include "../utility/utility.h"

Acceptor::Acceptor(std::shared_ptr<EventLoop> &loop, std::shared_ptr<Socket> &socket) : _loop(loop), _socket(socket)
{
    _socket->listen();
    _server_channel.reset(new Channel(_loop, _socket->getFd()));
    std::function<void()> cb = std::bind(&Acceptor::acceptNewConnection, this, _loop, _socket);
    _server_channel->setNewConnectionCallBack(cb);
    _server_channel->enableReading(); // 这里注册,默认模式为边缘触发
}

void Acceptor::acceptNewConnection(std::shared_ptr<EventLoop> loop, std::shared_ptr<Socket> socket)
{
    int client_sock = socket->accept();
    ERROR_CHECK(client_sock == -1, "new client connected error");

    std::function<void()> cb = std::bind(&EventLoop::handleReadConnection, _loop.get(), client_sock);
    Channel *ch = new Channel(loop, client_sock);
    ch->setReadConnectionCallBack(cb);
    ch->enableReading(); // 这里注册,默认模式为边缘触发

    std::cout << InetAddress::getRemoteAddress(client_sock); // 查域名这里会阻塞

    TcpControler *tcp = new TcpControler(client_sock);
    using socketoptions = AbstractControl::socketoption;
    tcp->setSocketOption(socketoptions::REUSEDADDRESS | socketoptions::REUSEDPORT | socketoptions::NONEBLOCKSOCKET);
    _loop->recordNewConnection(client_sock, tcp); // 这里传给了Evenloop共享指针自动销毁
}
