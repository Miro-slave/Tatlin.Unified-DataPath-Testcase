#include "insertion_sort.h"
#include "ram.h"
#include "tape.h"

#include <gtest/gtest.h>

using namespace tape;

TEST(InsertionSortTest, SortsCorrectly) {
  std::shared_ptr<IDurationCounter> counter = std::make_shared<DummyCounter>();

  std::unique_ptr<ITape<std::int32_t>> input = std::make_unique<FileTape<std::int32_t>>(
      "input_tape.csv",
      counter
  );

  std::unique_ptr<ITape<std::int32_t>> output = std::make_unique<FileTape<std::int32_t>>(
      "output_tape.csv",
      counter
  );

  std::vector<std::unique_ptr<ITape<std::int32_t>>> temp;

  std::vector<std::int32_t> ram_data(5, 0);

  std::unique_ptr<IRam<std::int32_t>> ram = std::make_unique<VectorRam<std::int32_t>>(ram_data);

  InsertionSort<std::int32_t> sorting_algorithm;
  sorting_algorithm.sort(input, output, temp, ram);

  output->moveToBegin();

  EXPECT_EQ(output->read(), 1);

  output->moveRight();
  EXPECT_EQ(output->read(), 2);

  output->moveRight();
  EXPECT_EQ(output->read(), 2);
}

TEST(InsertionSortTest, ThrowsIfRamTooSmall) {
  std::shared_ptr<IDurationCounter> counter = std::make_shared<DummyCounter>();

  std::unique_ptr<ITape<std::int32_t>> input = std::make_unique<FileTape<std::int32_t>>(
      "input_tape.csv",
      counter
  );

  std::unique_ptr<ITape<std::int32_t>> output = std::make_unique<FileTape<std::int32_t>>(
      "output_tape.csv",
      counter
  );

  std::vector<std::unique_ptr<ITape<std::int32_t>>> temp;

  std::vector<std::int32_t> ram_data(4, 0);

  std::unique_ptr<IRam<std::int32_t>> ram = std::make_unique<VectorRam<std::int32_t>>(ram_data);

  InsertionSort<std::int32_t> sorting_algorithm;

  EXPECT_THROW(
    sorting_algorithm.sort(input, output, temp, ram),
    std::runtime_error
  );
}
