#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

using ::testing::Test;

class AsyncDispatcherTestFixture : public ::testing::Test {
 protected:
  std::chrono::milliseconds m_waitingTime = std::chrono::milliseconds(100);
  AsyncDispatcher* m_pAsyncDispatcher;
  void SetUp() override { m_pAsyncDispatcher = new AsyncDispatcher(); };
  void TearDown() override {
    if (m_pAsyncDispatcher) {
      delete m_pAsyncDispatcher;
      m_pAsyncDispatcher = 0;
    }
  };
  void task(int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(m_waitingTime);
  }
};

TEST_F(AsyncDispatcherTestFixture, DispatchFunk_DispatchFunctionsNoSync_CanExecuteTasksA) {
  m_pAsyncDispatcher->dispatchFunc([this] { task(1); });
  m_pAsyncDispatcher->dispatchFunc([this] { task(2); });
  std::this_thread::sleep_for(3 * m_waitingTime);
}

TEST_F(AsyncDispatcherTestFixture,
       ResyncWithFunc_DispatchFunctionsAndResyncAfterExecution_CanExecuteTasksAndResync) {
  m_pAsyncDispatcher->dispatchFunc([this] { task(1); });
  m_pAsyncDispatcher->dispatchFunc([this] { task(2); });
  m_pAsyncDispatcher->resyncWithFunc();
}

TEST_F(
    AsyncDispatcherTestFixture,
    ResyncWithFunc_DispatchFunctionsAndResyncAfterExecutionMultipleTimes_CanExecuteAllTasksAndResync) {
  m_pAsyncDispatcher->dispatchFunc([this] { task(1); });
  m_pAsyncDispatcher->dispatchFunc([this] { task(2); });
  m_pAsyncDispatcher->resyncWithFunc();
  m_pAsyncDispatcher->dispatchFunc([this] { task(3); });
  m_pAsyncDispatcher->dispatchFunc([this] { task(4); });
  m_pAsyncDispatcher->resyncWithFunc();
}