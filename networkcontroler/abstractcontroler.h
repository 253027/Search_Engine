#ifndef __ABSTRACTCONTROLER_HEAD_H__
#define __ABSTRACTCONTROLER_HEAD_H__

#include <string>
#include <fcntl.h>

class InetAddress;

class AbstractControl
{
public:
    enum socketoption
    {
        REUSEDADDRESS,

        REUSEDPORT,

        NONEBLOCKSOCKET,

        ENDOFSOCKETPOPTION
    };

    virtual InetAddress getLocalAddress() = 0;

    InetAddress getRemoteAddress(int fd);

    virtual void setSocketOption(int option) = 0;

    virtual int send(std::string &buf, int size) = 0;

    virtual int recv(std::string &buf, int size) = 0;

private:
};

#endif //__ABSTRACTCONTROLER_HEAD_H__