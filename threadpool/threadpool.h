#ifndef __THREADPOOL_HEAD_H__
#define __THREADPOOL_HEAD_H__

#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
#include <future>
#include <queue>

class ThreadPool
{

public:
    ThreadPool(int threadnums, int maxqueuenums);

    void stop();

    template <class F, class... Args>
    auto appendThreadPool(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    volatile bool _stop;

    int _max_queue_size;

    std::vector<std::thread> _threads;

    std::mutex mutx;

    std::condition_variable condition;

    std::queue<std::function<void()>> _que;
};

template <class F, class... Args>
inline auto ThreadPool::appendThreadPool(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(mutx);

        if (_stop || _que.size() >= _max_queue_size)
            return res;

        _que.emplace([task]()
                     { (*task)(); });
    }
    condition.notify_one();
    return res;

    /*
    #include <iostream>
    #include <future>
    #include <functional>

    // 一个简单的函数，用于计算给定的数字的平方
    int square(int x)
    {
        return x * x;
    }

    int main()
    {
        // 创建一个 packaged_task，将可调用对象 square 包装起来
        std::packaged_task<int(int)> task(square);
        // 获取与 packaged_task 关联的 future 对象
        std::future<int> future = task.get_future();
        // 在另一个线程中执行 packaged_task
        std::thread(std::move(task), 5).detach();
        // 获取结果
        int result = future.get();
        std::cout << "The result is: " << result << std::endl;
        return 0;
    }
    */
}

#endif //__THREADPOOL_HEAD_H__
