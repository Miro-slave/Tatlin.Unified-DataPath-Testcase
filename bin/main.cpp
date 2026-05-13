#include "application.h"

#include <filesystem>
#include <iostream>

using tape::Application;

int main(int argc, char* argv[]) {
  try {
    Application application(argc, argv);
    application.run();
  } catch (const std::exception& err) {
    std::cout << err.what() << '\n';

    return 1;
  }

  return 0;
}
