#ifndef __CHANNEL_HEAD_H__
#define __CHANNEL_HEAD_H__

#include <unistd.h>
#include <cstdint>

class Channel
{
public:
    Channel(int fd, uint32_t option);

    void setCalledEvent(uint32_t option);

    ~Channel();

private:
    // 要监听的文件描述符集合
    int _socket_fd;
    // 注册的事件集合
    uint32_t _regist_event;
    // 触发的事件集合
    uint32_t _called_event;
};

#endif //__CHANNEL_HEAD_H__