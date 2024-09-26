#include "threadpool.h"

ThreadPool::ThreadPool(int threadnums, int maxqueuenums) : _stop(false), _max_queue_size(maxqueuenums)
{
    for (int i = 0; i < threadnums; i++)
    {
        _threads.emplace_back(std::thread([this]()
                                          {
                                              std::function<void()> task;
                                              while (1)
                                              {
                                                  {
                                                      std::unique_lock<std::mutex> lock(mutx);
                                                      condition.wait(lock, [this] { return _stop || !_que.empty(); });
                                                      if (_stop && _que.empty())
                                                          return;
                                                      task = _que.front();
                                                      _que.pop();
                                                  }
                                                  task();
                                              } }));
    }
}

void ThreadPool::stop()
{
    {
        std::lock_guard<std::mutex> guard(mutx);
        _stop = true;
    }
    condition.notify_all();
    for (auto &x : _threads)
    {
        if (!x.joinable())
            continue;
        x.join();
    }
}
