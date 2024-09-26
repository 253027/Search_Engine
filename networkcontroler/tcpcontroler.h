#ifndef __TCPCONTROLER_HEAD_H__
#define __TCPCONTROLER_HEAD_H__

#include <memory>
#include <string>
#include "abstractcontroler.h"
#include "iodevice.h"

class TcpControler : public AbstractControl
{
public:
    TcpControler(int socket);

    InetAddress getLocalAddress() override;

    void setSocketOption(int option) override;

    int recv(std::string &buf, int size = 0) override;

    int send(std::string &buf, int size = 0) override;

private:
    void setReusedAddress();

    void setReusedPort();

    void setNoneBlcokSocket();

    int _socket;

    std::shared_ptr<IoDevice> _device;
};

#endif //__TCPCONTROLER_HEAD_H__