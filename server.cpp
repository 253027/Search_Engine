#include "./tcpcontroler/tcpcontroler.h"
#include "./epoll/epoll.h"
#include <iostream>

int main()
{
    TcpControler tcp("127.0.0.1", 9190);
    Epoll fd;
    int t = tcp.accept();
    fd.addFileDescripter(t, EPOLLIN);
    return 0;
}