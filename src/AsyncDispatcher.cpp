#include "AsyncDispatcher/AsyncDispatcher.hpp"

#include <iostream>

AsyncDispatcher::AsyncDispatcher() : m_stop(false), m_forcedSync(false) {
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
  std::cout << "Resync after leaving scope of AsyncDispatcher obj" << std::endl;
  m_condVarWorker.notify_all();  // check if notify_one() is sufficient
}

void AsyncDispatcher::dispatchFunc(std::function<void()> func) {
  std::lock_guard<std::mutex> lock(m_mutexWorker);
  m_queue.push(std::move(func));  // check with emplace
  m_condVarWorker.notify_all();
}

void AsyncDispatcher::workerThread() {
  do {
    std::unique_lock<std::mutex> lock(m_mutexWorker);
    m_condVarWorker.wait(lock, [this] { return m_stop || m_queue.size() > 0; });
    if (m_queue.size() > 0) {
      std::cout << "Processing " << m_queue.size() << "task(s)" << std::endl;
      auto func = std::move(m_queue.front());
      m_queue.pop();
      func();
    }
    if (m_queue.size() == 0) {
      std::cout << "Thread " << std::this_thread::get_id() << " triggers resync" << std::endl;
      m_forcedSync = true;
      m_condVarWorker.notify_all();
    }
  } while (m_stop != true);
}

void AsyncDispatcher::resyncWithFunc() {
  std::unique_lock<std::mutex> lock(m_mutexWorker);
  std::cout << "Thread " << std::this_thread::get_id() << " waits for resync" << std::endl;
  m_condVarWorker.wait(lock, [this] { return m_forcedSync; });
  m_forcedSync = false;
  std::cout << "Thread " << std::this_thread::get_id() << " was synced" << std::endl;
}