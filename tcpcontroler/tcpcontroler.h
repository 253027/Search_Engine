#ifndef __TCPCONTROLER_HEAD_H__
#define __TCPCONTROLER_HEAD_H__

#include <memory>
#include <string>
#include "../socket/socket.h"
#include "../inetaddress/inetaddress.h"

class TcpControler
{
public:
    TcpControler(const std::string &ip, int16_t port);

    int accept();

    InetAddress getLocalAddress();

    InetAddress getRemoteAddress();

private:
    std::shared_ptr<InetAddress> _address;

    std ::shared_ptr<Socket> _socket;
};

#endif //__TCPCONTROLER_HEAD_H__