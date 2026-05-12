//
// Created by YF on 12.05.2026.
//

#include "insertion_sort.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <memory>

using tape::ITape;
using tape::IRam;
using tape::ISortingAlgorithm;
using tape::FileTape;
using tape::VectorRam;
using tape::InsertionSort;

int main(int argc, char* argv[]) {
  try {
    if (argc != 3 && argc != 4) {
      std::cout << "Invalid args count: " << argc << " instead of 2 or 3\n"
          << "Usage options: tape_app <input fle path> <output file path>\n"
          << "tape_app <input fle path> <output file path> <output file path> <config file path>\n";

      return 1;
    }

    ISortingAlgorithm<std::uint32_t>* insertion_sort = new InsertionSort<std::uint32_t>();

    std::vector<std::uint32_t> input_data = { 32432432, 12, 2, 4, 2, 1 };
    std::vector<std::uint32_t> ram_data(6, 0);

    std::string input_file_path = argv[1];
    std::string output_file_path = argv[2];

    /*  std::ofstream ofs(output_file_path);

      std::ostream_iterator<int> ofs_it(ofs, ",");

      // ofs.seekp(0);

      for (std::size_t i(0); i != input_data.size(); i++, ofs_it++) {
        *ofs_it = static_cast<std::uint32_t>(input_data[i]);
      }

      return 0;*/

    std::unique_ptr<ITape<std::uint32_t>> input_tape = std::make_unique<FileTape<std::uint32_t>>(input_file_path);
    std::unique_ptr<ITape<std::uint32_t>> output_tape = std::make_unique<FileTape<std::uint32_t>>(output_file_path);

    std::vector<std::unique_ptr<ITape<std::uint32_t>>> temp_tapes;
    std::unique_ptr<IRam<std::uint32_t>> ram = std::make_unique<VectorRam<std::uint32_t>>(ram_data);

    insertion_sort->sort(input_tape, output_tape, temp_tapes, ram);
  } catch (const std::exception& err) {
    std::cout << err.what() << '\n';

    return 1;
  }


  return 0;
}
