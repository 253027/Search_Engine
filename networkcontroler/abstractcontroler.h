#ifndef __ABSTRACTCONTROLER_HEAD_H__
#define __ABSTRACTCONTROLER_HEAD_H__

class InetAddress;

class AbstractControl
{
public:
    enum socketoption
    {
        REUSEEDADDRESS,

        REUSEEDPORT,

        ENDOFSOCKETPOPTION
    };

    virtual InetAddress getLocalAddress() = 0;

    InetAddress getRemoteAddress(int fd);

    virtual void setSocketOption(int option) = 0;

private:
};

#endif //__ABSTRACTCONTROLER_HEAD_H__