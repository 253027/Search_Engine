#include "./tcpserver/tcpserver.h"
#include <iostream>

int main()
{
    TcpServer server("127.0.0.1", 9190);
    server.start();
    return 0;
}