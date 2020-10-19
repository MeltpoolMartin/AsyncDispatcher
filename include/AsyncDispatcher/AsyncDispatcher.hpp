#ifndef ASYNC_DISPATCHER
#define ASYNC_DISPATCHER

#include <functional>
#include <queue>
#include <thread>

class AsyncDispatcher {
 public:
  AsyncDispatcher();
  virtual ~AsyncDispatcher();
  void dispatchFunc(std::function<void()> func);

 private:
  void stop();
  void workerThread();
  std::queue<std::function<void()>> m_queue;
  std::mutex m_mutexWorker;
  std::condition_variable m_condVarWorker;
  std::thread m_threadWorker;
  bool m_stop;
};

#endif