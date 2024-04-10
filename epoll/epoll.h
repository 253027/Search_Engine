#ifndef __EPOLL_HEAD_H__
#define __EPOLL_HEAD_H__

#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <unordered_set>

class Channel;

class Epoll
{
public:
    Epoll();

    ~Epoll();

    void addFileDescripter(int fd, uint32_t option);

    std::vector<Channel *> epoll_wait(int timeout = -1);

private:
    int _epoll_fd;

    std::vector<struct epoll_event> events;

    // 用户记录已申请的Channel类堆内存
    std::unordered_set<Channel *> memo;
};

#endif //__EPOLL_HEAD_H__