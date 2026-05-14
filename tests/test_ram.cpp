#include "ram.h"

#include <gtest/gtest.h>

using namespace tape;

TEST(VectorRamTest, ReadWriteWorks) {
  std::vector<std::int32_t> data = {1, 2, 3};

  VectorRam<std::int32_t> ram(data);

  EXPECT_EQ(ram.read(0), 1);
  EXPECT_EQ(ram.read(1), 2);

  ram.write(1, 42);

  EXPECT_EQ(ram.read(1), 42);
}
