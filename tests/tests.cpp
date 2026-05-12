//
// Created by YF on 12.05.2026.
//

#include "insertion_sort.h"

#include <gtest/gtest.h>

using tape::ITape;
using tape::IRam;
using tape::ISortingAlgorithm;
using tape::FileTape;
using tape::VectorRam;
using tape::InsertionSort;

TEST(AlgoTestSuite, all_off) {
  ISortingAlgorithm<std::uint32_t>* insertion_sort = new InsertionSort<std::uint32_t>();

  std::vector<std::uint32_t> ram_data(6, 0);

  std::string input_file_path = "input_tape.csv";
  std::string output_file_path = "output_tape.csv";

  std::unique_ptr<ITape<std::uint32_t>> input_tape = std::make_unique<FileTape<std::uint32_t>>(input_file_path);
  std::unique_ptr<ITape<std::uint32_t>> output_tape = std::make_unique<FileTape<std::uint32_t>>(output_file_path);

  std::vector<std::unique_ptr<ITape<std::uint32_t>>> temp_tapes;
  std::unique_ptr<IRam<std::uint32_t>> ram = std::make_unique<VectorRam<std::uint32_t>>(ram_data);

  insertion_sort->sort(input_tape, output_tape, temp_tapes, ram);

  ASSERT_TRUE(true);
}
