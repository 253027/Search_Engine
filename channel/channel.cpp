#include "channel.h"

Channel::Channel(int fd, uint32_t option) : _socket_fd(fd), _regist_event(option)
{
    ;
}

void Channel::setCalledEvent(uint32_t option)
{
    _called_event = option;
}

Channel::~Channel()
{
}
