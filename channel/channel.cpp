#include "channel.h"

Channel::Channel(int fd, uint32_t option) : _socket_fd(fd), _regist_event(option)
{
    ;
}

void Channel::handleEvent()
{
    _call_back();
}

void Channel::setCalledEvent(uint32_t option)
{
    _called_event = option;
}

void Channel::setCallBack(const std::function<void()> &cb)
{
    //_call_back = cb;
}

Channel::~Channel()
{
    ;
}

int Channel::getRegistEvent()
{
    return _regist_event;
}

int Channel::getCalledEvent()
{
    return _called_event;
}

int Channel::getFileDescripter()
{
    return _socket_fd;
}
