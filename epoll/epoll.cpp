#include "epoll.h"
#include "../utility/utility.h"
#include "../channel/channel.h"

Epoll::Epoll() : _epoll_fd(-1), events(1024)
{
    _epoll_fd = ::epoll_create1(0);
    ERROR_CHECK(_epoll_fd == -1, "epoll fd create failed");
    ERROR_CHECK((events.size() == 0), "epoll_events array allocate failed");
}

Epoll::~Epoll()
{
    if (_epoll_fd != -1)
        ::close(_epoll_fd);
    for (auto &x : memo)
        delete x;
}

void Epoll::addFileDescripter(int fd, uint32_t option)
{
    struct epoll_event event;
    ::memset(&event, 0, sizeof(event));
    Channel *ch = new Channel(fd, option);
    ERROR_CHECK((ch == nullptr), "Class Channel allocate failed");

    event.events = option;
    event.data.ptr = static_cast<void *>(ch);

    int ret = ::epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret == -1, "add file descripter failed");
}

std::vector<Channel *> Epoll::epoll_wait(int timeout)
{
    std::vector<Channel *> res;
    int nums = ::epoll_wait(_epoll_fd, events.data(), events.size(), timeout);
    ERROR_CHECK(nums == -1, "epoll_wait error");
    if (nums == events.size())
        events.resize(nums << 1);
    for (int i = 0; i < nums; i++)
    {
        res.emplace_back(static_cast<Channel *>(events[i].data.ptr));
        res.back()->setCalledEvent(events[i].events);
    }
    return res;
}
