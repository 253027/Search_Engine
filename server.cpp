#include "./networkcontroler/tcpcontroler.h"
#include "./epoll/epoll.h"
#include <iostream>

int main()
{
    TcpControler tcp("127.0.0.1", 9190);
    tcp.setSocketOption(AbstractControl::socketoption::REUSEEDADDRESS | AbstractControl::socketoption::REUSEEDPORT);
    tcp.connect();
    return 0;
}