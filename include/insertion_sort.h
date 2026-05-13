//
// Created by YF on 12.05.2026.
//

#include "sorting_algorithm.h"

#ifndef TESTCASE1_INSERTION_SORT_H
#define TESTCASE1_INSERTION_SORT_H

namespace tape {
  template <typename T>
  class InsertionSort : public ISortingAlgorithm<T> {
   public:
    void sort(std::unique_ptr<ITape<T>>& input_tape,
              std::unique_ptr<ITape<T>>& output_tape,
              std::vector<std::unique_ptr<ITape<T>>>& temp_tapes,
              std::unique_ptr<IRam<T>>& ram) override
    {
      if (ram->size() < 4) {
        throw std::runtime_error("Insertion sort requires at least 4 RAM cells");
      }

      ram->write(INPUT_LEN, static_cast<T>(input_tape->size())); // Initialization
      ram->write(ITERATION, 1);
      ram->write(INDEX_I, 0);
      ram->write(CURRENT_ELEMENT, input_tape->read());
      ram->write(NEIGHBOURING_ELEMENT, 0);

      while (ram->read(ITERATION) <= ram->read(INPUT_LEN)) { // Algorithm
        ram->write(CURRENT_ELEMENT, input_tape->read());

        while (ram->read(INDEX_I) != 0) {
          input_tape->moveLeft();
          ram->write(NEIGHBOURING_ELEMENT, input_tape->read());
          input_tape->moveRight();

          if (ram->read(CURRENT_ELEMENT) < ram->read(NEIGHBOURING_ELEMENT)) { // Swap elements
            input_tape->write(ram->read(NEIGHBOURING_ELEMENT));
            input_tape->moveLeft();
            input_tape->write(ram->read(CURRENT_ELEMENT));

            ram->write(INDEX_I, ram->read(INDEX_I) - 1);
          } else {
            break;
          }
        }

        while (ram->read(INDEX_I) < ram->read(ITERATION)) { // Move to the next element
          ram->write(INDEX_I, ram->read(INDEX_I) + 1);
          input_tape->moveRight();
        }

        ram->write(ITERATION, ram->read(ITERATION) + 1);
      }

      input_tape->moveToBegin(); // Write to output
      ram->write(INDEX_I, 0);

      while (ram->read(INDEX_I) < ram->read(INPUT_LEN)) {
        output_tape->write(input_tape->read());
        input_tape->moveRight();
        output_tape->moveRight();
        std::cout << input_tape->read() << '\n';
        ram->write(INDEX_I, ram->read(INDEX_I) + 1);
      }
    };

  private:
    enum ERamOffset {
      INPUT_LEN = 0,
      ITERATION = 1,
      INDEX_I = 2,
      CURRENT_ELEMENT = 3,
      NEIGHBOURING_ELEMENT = 4
    };
  };
};

#endif //TESTCASE1_INSERTION_SORT_H