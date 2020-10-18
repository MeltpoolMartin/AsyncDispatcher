#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

TEST(AsyncDispatcherTestSuite, Constructor_CheckConstructionAndDestruction) {
  AsyncDispatcher asyncDispatcher;
  auto task = [](int taskNumber) {
    std::cout << "task " << taskNumber << " with thread ID " << std::this_thread::get_id()
              << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  };
  asyncDispatcher.dispatchFunc([&task] { task(1); });
  asyncDispatcher.dispatchFunc([&task] { task(2); });
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_TRUE(true);
}