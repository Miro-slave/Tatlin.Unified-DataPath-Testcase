//
// Created by YF on 12.05.2026.
//

#include "ram.h"
#include "tape.h"

#include <memory>

#ifndef TESTCASE1_SORTING_ALGORITHM_H
#define TESTCASE1_SORTING_ALGORITHM_H

namespace tape {
  template <typename T>
  class ISortingAlgorithm {
  public:
    virtual void sort(std::unique_ptr<ITape<T>>& input_tape,
              std::unique_ptr<ITape<T>>& output_tape,
              std::vector<std::unique_ptr<ITape<T>>>& temp_tapes,
              std::unique_ptr<IRam<T>>& ram) = 0;
  };
};

#endif //TESTCASE1_SORTING_ALGORITHM_H