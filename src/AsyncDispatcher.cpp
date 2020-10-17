#include "AsyncDispatcher/AsyncDispatcher.hpp"

AsyncDispatcher::AsyncDispatcher() : m_stop(false) {
  m_threadWorker = std::thread([this] { workerThread(); });
}

AsyncDispatcher::~AsyncDispatcher() {
  stop();
  if (m_threadWorker.joinable()) {
    m_threadWorker.join();
  }
}

void AsyncDispatcher::stop() {
  m_stop = true;
  m_condVarWorker.notify_all();  // check if notify_one() is sufficient
}

void AsyncDispatcher::dispatchFunc(std::function<void()> func) {
  std::lock_guard<std::mutex> lock(m_mutexWorker);
  m_queue.push(std::move(func));  // check with emplace
  m_condVarWorker.notify_all();
}

void AsyncDispatcher::workerThread() {
  std::unique_lock<std::mutex> lock(m_mutexWorker);
  do {
    m_condVarWorker.wait(lock, [this] { return m_stop || m_queue.size(); });
    if (m_queue.size()) {
      auto func = std::move(m_queue.front());
      func();
    }
  } while (m_stop != true);
}