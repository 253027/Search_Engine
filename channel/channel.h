#ifndef __CHANNEL_HEAD_H__
#define __CHANNEL_HEAD_H__

#include <unistd.h>
#include <cstdint>
#include <functional>

class Channel
{
public:
    Channel(int fd, uint32_t option);

    void handleEvent();

    void setCalledEvent(uint32_t option);

    void setCallBack(const std::function<void()> &cb);

    int getRegistEvent();

    int getCalledEvent();

    int getFileDescripter();

    ~Channel();

private:
    // 要监听的文件描述符集合
    int _socket_fd;
    // 注册的事件集合
    uint32_t _regist_event;
    // 触发的事件集合
    uint32_t _called_event;

    std::function<void()> _call_back;
};

#endif //__CHANNEL_HEAD_H__