#ifndef __EPOLL_HEAD_H__
#define __EPOLL_HEAD_H__

#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <vector>
#include <unordered_set>

class Channel;

class Epoll
{
public:
    Epoll();

    ~Epoll();

    void updateChannel(Channel *channel); // 这个是提供给eventloop使用的

    std::vector<Channel *> epoll_wait(int timeout = -1);

private:
    int _epoll_fd;

    std::vector<struct epoll_event> events;
    // 用户记录已申请的Channel类堆内存
    std::unordered_set<Channel *> memo;
};

#endif //__EPOLL_HEAD_H__