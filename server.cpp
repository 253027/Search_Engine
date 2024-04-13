#include "./tcpserver/tcpserver.h"
#include "./threadpool/threadpool.h"
#include <iostream>

void task()
{
    std::cout << pthread_self() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    // TcpServer server("172.21.40.143", 9190);
    // server.start();
    ThreadPool pool(3, 10);
    for (int i = 0; i < 20; i++)
        pool.appendThreadPool(task);
    pool.stop();
    return 0;
}
