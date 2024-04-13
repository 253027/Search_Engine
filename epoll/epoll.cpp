#include "epoll.h"
#include "../utility/utility.h"
#include "../channel/newconchannel.h"
#include "../channel/readeventchannel.h"

Epoll::Epoll() : _epoll_fd(-1), events(1024)
{
    _epoll_fd = ::epoll_create(1);
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

void Epoll::updateChannel(Channel *channel)
{
    int fd = channel->getFileDescripter();
    memo.insert(channel);
    struct epoll_event event;
    ::memset(&event, 0, sizeof(event));
    event.events = channel->getRegistEvent();
    event.data.ptr = static_cast<void *>(channel);
    if (channel->isInEpoll())
        ERROR_CHECK(epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &event) == -1, "epoll modify failed");
    else
        ERROR_CHECK(epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1, "epoll add failed"), channel->setInEpoll();
}

std::vector<Channel *> Epoll::epoll_wait(int timeout)
{
    std::vector<Channel *> res;
    int nums = ::epoll_wait(_epoll_fd, events.data(), events.size(), timeout);
    ERROR_CHECK(nums == -1 && (errno != EINTR), "epoll_wait error");
    if (nums == events.size())
        events.resize(nums << 1);
    for (int i = 0; i < nums; i++)
    {
        res.emplace_back(static_cast<Channel *>(events[i].data.ptr));
        res.back()->setCalledEvent(events[i].events);
    }
    return res;
}
