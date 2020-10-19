#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

TEST(AsyncDispatcherTestSuite, Constructor_CheckConstructionAndDestruction) {
  AsyncDispatcher asyncDispatcher;
  auto task = [](int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
  asyncDispatcher.dispatchFunc([&task] { task(1); });
  asyncDispatcher.dispatchFunc([&task] { task(2); });
  asyncDispatcher.resyncWithFunc();
  asyncDispatcher.dispatchFunc([&task] { task(3); });
  EXPECT_TRUE(true);
  std::cout << "Main function leaves scope" << std::endl;
}