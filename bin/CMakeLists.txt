add_executable(tape_app main.cpp)

target_link_libraries(tape_app
        PRIVATE tape_lib
)

target_include_directories(tape_app
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
