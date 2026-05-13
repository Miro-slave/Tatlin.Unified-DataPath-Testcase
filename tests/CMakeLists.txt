add_executable(tests
        test_ram.cpp
        test_duration_counter.cpp
        test_insertion_sort.cpp
)

find_package(GTest)

target_link_libraries(tests
        gtest::gtest
        tape_lib)

configure_file(
        ${CMAKE_SOURCE_DIR}/samples/input_tape.csv
        ${CMAKE_BINARY_DIR}/tests/input_tape.csv
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/samples/output_tape.csv
        ${CMAKE_BINARY_DIR}/tests/output_tape.csv
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/samples/config.json
        ${CMAKE_BINARY_DIR}/tests/config.json
        COPYONLY
)
