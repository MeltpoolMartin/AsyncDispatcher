#include <iostream>

#include "AsyncDispatcher/AsyncDispatcher.hpp"
#include "gtest/gtest.h"

TEST(AsyncDispatcherTestSuite, Constructor_CheckConstructionAndDestruction) {
  AsyncDispatcher asyncDispatcher;
  asyncDispatcher.dispatchFunc([] { std::cout << "calc 5 * 2 = " << 5 * 2 << std::endl; });
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_TRUE(true);
}