#include "channel.h"
#include "../eventloop/eventloop.h"

Channel::Channel(std::shared_ptr<EventLoop> &loop, int fd) : _is_in_epoll(false), _socket_fd(fd), _loop(loop)

{
    ;
}

void Channel::setCalledEvent(uint32_t option)
{
    _called_event = option;
}

void Channel::headleReadConnectionEvent()
{
    _call_back_read_connection();
}

int Channel::getRegistEvent()
{
    return _regist_event;
}

int Channel::getCalledEvent()
{
    return _called_event;
}

bool Channel::isInEpoll()
{
    return _is_in_epoll;
}

void Channel::handleNewConnectionEvent()
{
    _call_back_newconnection();
}

void Channel::setInEpoll()
{
    _is_in_epoll = true;
}

void Channel::enableReading()
{
    _regist_event = EPOLLIN | EPOLLET;
    _loop->updateChannel(this);
}

int Channel::getFileDescripter()
{
    return _socket_fd;
}
