#ifndef __INETADDRESS_HEAD_H__
#define __INETADDRESS_HEAD_H__

#include <arpa/inet.h>
#include <string>

class InetAddress
{
public:
    InetAddress(const std::string &ip, int16_t port);

    InetAddress(const struct sockaddr_in &addr);

    std::string ip() const;

    uint16_t port() const;

    ~InetAddress();

private:
    struct sockaddr_in _addr;

    socklen_t _addr_len;
};

#endif //__INETADDRESS_HEAD_H__