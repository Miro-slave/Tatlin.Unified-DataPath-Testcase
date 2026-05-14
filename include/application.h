#include "insertion_sort.h"

#include <memory>

#ifndef TAPE_APPLICATION_H
#define TAPE_APPLICATION_H

namespace tape {
  class Application {
   public:
    Application(int argc, char* argv[]);
    void run();

   private:
    std::unique_ptr<ITape<std::int32_t>> input_tape_;
    std::unique_ptr<ITape<std::int32_t>> output_tape_;
    std::vector<std::unique_ptr<ITape<std::int32_t>>> temp_tapes_;
    std::unique_ptr<IRam<std::int32_t>> ram_;
    std::shared_ptr<IDurationCounter> duration_counter_;
    std::unique_ptr<ISortingAlgorithm<std::int32_t>> sorting_algorithm_;
    std::size_t m_;
  };
};

#endif //TAPE_APPLICATION_H