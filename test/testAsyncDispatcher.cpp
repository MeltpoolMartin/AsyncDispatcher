#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

TEST(AsyncDispatcherTestSuite,
     ResyncWithFunc_DispatchFunctionsAndResyncAfterExecution_CanExecuteTasksAndResync) {
  auto waitingTime = std::chrono::milliseconds(100);
  AsyncDispatcher asyncDispatcher;
  auto task = [&waitingTime](int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(waitingTime);
  };
  asyncDispatcher.dispatchFunc([&task] { task(1); });
  asyncDispatcher.dispatchFunc([&task] { task(2); });
  asyncDispatcher.resyncWithFunc();
}

TEST(AsyncDispatcherTestSuite, DispatchFunk_DispatchFunctionsNoSync_CanExecuteTasksA) {
  auto waitingTime = std::chrono::milliseconds(100);
  AsyncDispatcher asyncDispatcher;
  auto task = [&waitingTime](int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(waitingTime);
  };
  asyncDispatcher.dispatchFunc([&task] { task(1); });
  asyncDispatcher.dispatchFunc([&task] { task(2); });
  std::this_thread::sleep_for(3 * waitingTime);
}