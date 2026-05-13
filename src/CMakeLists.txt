add_library(tape_lib
        application.cpp)

find_package(nlohmann_json)

target_include_directories(tape_lib PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tape_lib
        nlohmann_json::nlohmann_json)
