#ifndef __INETADDRESS_HEAD_H__
#define __INETADDRESS_HEAD_H__

#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <cstring>

class InetAddress
{
public:
    InetAddress(const std::string &ip, int16_t port);

    InetAddress(const struct sockaddr_in &addr);

    std::string ip() const;

    uint16_t port() const;

    const struct sockaddr_in *getAddress() const;

    static InetAddress getRemoteAddress(int fd);

    friend std::ostream &operator<<(std::ostream &os, const InetAddress &addr);

private:
    struct sockaddr_in _addr;

    socklen_t _addr_len;
};

#endif //__INETADDRESS_HEAD_H__