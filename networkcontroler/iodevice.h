#ifndef __IODEVICE_HEAD_H__
#define __IODEVICE_HEAD_H__

#include <string>
#include <unistd.h>
#include <sys/socket.h>

class IoDevice
{
public:
    IoDevice(int socket);

    int boundary_recv(std::string &buf);

    int boundary_send(const std::string &buf);

    int send(const std::string &buf);

    int recv(std::string &buf);

private:
    int _socket;

    std::string _iobuf;
};

#endif //__IODEVICE_HEAD_H__