#include "inetaddress.h"
#include <cstring>

InetAddress::InetAddress(const std::string &ip, int16_t port) : _addr_len(sizeof(_addr))
{
    ::memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
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

InetAddress::~InetAddress() {}
