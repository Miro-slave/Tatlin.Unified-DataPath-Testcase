//
// Created by YF on 12.05.2026.
//

#include "application.h"
#include "duration_counter.h"
#include "insertion_sort.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <memory>

using tape::Application;

int main(int argc, char* argv[]) {
  try {
    Application application(argc, argv);
    application.run();
  } catch (const std::exception& err) {
    std::cout << err.what() << '\n';

    return 1;
  }
  Application application(argc, argv);

  return 0;
}
