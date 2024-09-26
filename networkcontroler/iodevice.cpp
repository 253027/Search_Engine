#include "iodevice.h"
#include "../utility/utility.h"

IoDevice::IoDevice(int socket) : _socket(socket) {}

int IoDevice::boundary_recv(std::string &buf)
{
    char buffer[1024];
    int ret = ::recv(_socket, buffer, 8, MSG_WAITALL);
    ERROR_CHECK(ret == -1, "boundary recv error which is -1");
    if (ret == 0)
        return 0;
    size_t len = *(size_t *)buffer, hash_recv = 0;
    while ((ret = ::recv(_socket, buffer, std::min(1024UL, len - hash_recv), MSG_WAITALL)) > 0)
    {
        if (ret == -1 && (errno & EAGAIN))
            continue;
        else if (ret == -1)
            return -1;
        buf.append(buffer, ret), hash_recv += ret;
    }
    return hash_recv;
}

int IoDevice::boundary_send(const std::string &buf)
{
    size_t len = buf.size(), has_send = 0;
    int ret = ::send(_socket, &len, sizeof(len), 0);
    ERROR_CHECK(ret == -1, "boundary send data size error");
    return send(buf);
}

int IoDevice::send(const std::string &buf)
{
    int ret;
    size_t len = buf.size(), has_send = 0;
    while ((ret = ::send(_socket, buf.data() + has_send, std::min(1024UL, len - has_send), 0)) > 0)
    {
        if (ret == -1 && (errno & EWOULDBLOCK))
            continue;
        else if (ret == -1)
            return -1;
        has_send += ret;
    }
    return has_send;
}

int IoDevice::recv(std::string &buf)
{
    int ret = 0, bytes_read = 0;
    char buffer[1024];
    while ((ret = ::read(_socket, buffer, 1024)) > 0)
    {
        if (ret == -1)
            return (errno & EAGAIN) ? bytes_read : -1;
        buf.append(buffer, ret), bytes_read += ret;
    }
    return bytes_read;
}
