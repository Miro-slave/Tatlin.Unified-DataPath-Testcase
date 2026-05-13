#include "duration_counter.h"

#include <gtest/gtest.h>

using namespace tape;

TEST(DummyCounterTest, OperationsIncreaseTime) {
  DummyCounter counter;

  EXPECT_EQ(counter.totalOperationTime(), 0);

  counter.read();
  counter.write();
  counter.moveLeft();

  EXPECT_EQ(counter.totalOperationTime(), 3);
}

TEST(DurationCounterTest, ReadsValuesFromConfig) {
  DurationCounter counter("config.json");

  EXPECT_EQ(counter.moveRight(), 3);
  EXPECT_EQ(counter.moveLeft(), 3);
  EXPECT_EQ(counter.moveToBegin(), 5);
  EXPECT_EQ(counter.write(), 2);
}

TEST(DurationCounterTest, TotalTimeAccumulates) {
  DurationCounter counter("config.json");

  counter.read();
  counter.read();
  counter.moveRight();

  EXPECT_EQ(counter.totalOperationTime(), 7);
}

TEST(DurationCounterTest, ThrowsIfConfigNotExists) {
  EXPECT_THROW(
      DurationCounter("missing.json"),
      std::runtime_error
  );
}
