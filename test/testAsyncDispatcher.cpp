#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

TEST(AsyncDispatcherTestSuite,
     ResyncWithFunc_DispatchFunctionsAndResyncAfterExecution_CanExecuteTasksAndResync) {
  AsyncDispatcher asyncDispatcher;
  auto task = [](int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  };
  asyncDispatcher.dispatchFunc([&task] { task(1); });
  asyncDispatcher.dispatchFunc([&task] { task(2); });
  asyncDispatcher.resyncWithFunc();
}