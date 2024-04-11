#ifndef __CHANNEL_HEAD_H__
#define __CHANNEL_HEAD_H__

#include <unistd.h>
#include <cstdint>
#include <memory>
#include <functional>
#include <sys/epoll.h>

class EventLoop;

class Channel
{
public:
    Channel(EventLoop *loop, int fd);

    void handleEvent();

    void setCalledEvent(uint32_t option);

    inline void setCallBack(std::function<void()> cb) { _call_back = cb; };

    bool isInEpoll();

    void setInEpoll();

    int getRegistEvent();

    int getCalledEvent();

    int getFileDescripter();

    void enableReading();

    ~Channel();

private:
    std::function<void()> _call_back;
    // epoll调用updatechaannel时避免重复添加
    bool _is_in_epoll;
    // 要监听的文件描述符集合
    int _socket_fd;

    std::shared_ptr<EventLoop> _loop;
    // 注册的事件集合
    uint32_t _regist_event;
    // 触发的事件集合
    uint32_t _called_event;
};

#endif //__CHANNEL_HEAD_H__