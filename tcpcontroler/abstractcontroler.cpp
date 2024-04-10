#include "abstractcontroler.h"
#include "../inetaddress/inetaddress.h"

InetAddress AbstractControl::getRemoteAddress(int fd)
{
    return InetAddress::getRemoteAddress(fd);
}