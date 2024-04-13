#include "./tcpserver/tcpserver.h"
#include "./threadpool/threadpool.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void task()
{
    std::cout << pthread_self() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

TcpServer *server;
ThreadPool *pool;

void stop(int sig)
{
    if (sig != SIGINT && sig != SIGKILL)
        return;
    server->stop();
    pool->stop();
    std::cout << "server closed" << std::endl;
}

int main()
{
    signal(SIGINT, stop);
    server = new TcpServer("127.0.0.1", 9190);
    pool = new ThreadPool(5, 50000);
    server->start();
    return 0;
}
