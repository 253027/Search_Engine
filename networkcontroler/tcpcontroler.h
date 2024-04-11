#ifndef __TCPCONTROLER_HEAD_H__
#define __TCPCONTROLER_HEAD_H__

#include <memory>
#include <string>
#include "abstractcontroler.h"
#include "../socket/socket.h"

class TcpControler : public AbstractControl
{
public:
    TcpControler(const std::string &ip, int16_t port);

    int accept();

    int getSocket() const; // 返回服务器端套接字文件描述符

    InetAddress getLocalAddress() override;

    void setSocketOption(int option) override;

private:
    void setReusedAddress();

    void setReusedPort();

    std::shared_ptr<InetAddress> _address;

    std ::shared_ptr<Socket> _socket;
};

#endif //__TCPCONTROLER_HEAD_H__