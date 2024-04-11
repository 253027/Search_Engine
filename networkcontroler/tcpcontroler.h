#ifndef __TCPCONTROLER_HEAD_H__
#define __TCPCONTROLER_HEAD_H__

#include <memory>
#include <string>
#include "abstractcontroler.h"

class TcpControler : public AbstractControl
{
public:
    TcpControler(int socket);

    InetAddress getLocalAddress() override;

    void setSocketOption(int option) override;

private:
    void setReusedAddress();

    void setReusedPort();

    int _socket;

    std::shared_ptr<InetAddress> _address;
};

#endif //__TCPCONTROLER_HEAD_H__