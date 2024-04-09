#include "inetaddress.h"
#include "../utility/utility.h"
#include <cstring>

InetAddress::InetAddress(const std::string &ip, int16_t port) : _addr_len(sizeof(_addr))
{
    ::memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    ERROR_CHECK(_addr.sin_addr.s_addr == -1, "input ip is invalid");
    _addr.sin_port = ::htons(port);
}

InetAddress::InetAddress(const sockaddr_in &addr) : _addr(addr) {}

std::string InetAddress::ip() const
{
    return ::inet_ntoa(_addr.sin_addr);
}

uint16_t InetAddress::port() const
{
    return ::ntohs(_addr.sin_port);
}

const sockaddr_in *InetAddress::getAddress() const
{
    return &_addr;
}

InetAddress InetAddress::getRemoteAddress(int fd)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    ERROR_CHECK(::getpeername(fd, (struct sockaddr *)&addr, &addr_len) == -1, "getRemoteAddress error");
    return addr;
}

InetAddress::~InetAddress() {}

std::ostream &operator<<(std::ostream &os, const InetAddress &addr)
{
    os << "ip: " << addr.ip() << " port: " << addr.port() << std::endl;
    return os;
}
