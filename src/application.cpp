#include "application.h"

#include "duration_counter.h"
#include "insertion_sort.h"

#include <iostream>

namespace tape {
  Application::Application(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
      std::cout << "Invalid args count: " << argc << " instead of 2 or 3\n"
          << "Usage options:\n"
          << "tape_app <input fle path> <output file path>\n"
          << "tape_app <input fle path> <output file path> <config file path>\n";

      throw std::runtime_error("Invalid arguments count");
    }

    sorting_algorithm_ = std::make_unique<InsertionSort<std::int32_t>>();

    std::string input_file_path = argv[1];
    std::string output_file_path = argv[2];

    if (argc == 3) {
      m_ = 5;
      duration_counter_ = std::make_shared<DummyCounter>();
    } else if (argc == 4) {
      std::string config_file_path = argv[3];

      std::ifstream ifs(config_file_path);

      if (!ifs.is_open()) {
        throw std::runtime_error("Cannot access the " + config_file_path + " file");
      }

      json config_data = json::parse(ifs);
      m_ = config_data["m"].get<std::size_t>();

      duration_counter_ = std::make_shared<DurationCounter>(config_file_path);
    }

    input_tape_ = std::make_unique<FileTape<std::int32_t>>(input_file_path, duration_counter_);
    output_tape_ = std::make_unique<FileTape<std::int32_t>>(output_file_path, duration_counter_, true);

    if (input_tape_->size() != output_tape_->size()) {
      throw std::runtime_error("Input and output files has different sizes");
    }

    std::vector<std::int32_t> ram_data(m_, 0);

    ram_ = std::make_unique<VectorRam<std::int32_t>>(ram_data);
  }

  void Application::run() {
    sorting_algorithm_->sort(input_tape_, output_tape_, temp_tapes_, ram_);

    std::cout << "Total operation time: " << duration_counter_->totalOperationTime() << '\n';
  }
};
