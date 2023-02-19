cmake_minimum_required(VERSION 3.24)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test test.cpp logger.hpp command.hpp parser.hpp settings.hpp sequential_calculator.hpp parallel_calculator.hpp parser.cpp command.cpp logger.cpp parallel_calculator.cpp sequential_calculator.cpp settings_parser.cpp settings_parser.hpp creator_by_file.cpp creator_by_file.hpp)
target_link_libraries(test gtest_main)


add_executable(calculator main.cpp logger.hpp command.hpp parser.hpp settings.hpp sequential_calculator.hpp parallel_calculator.hpp parser.cpp command.cpp logger.cpp parallel_calculator.cpp sequential_calculator.cpp settings_parser.cpp settings_parser.hpp creator_by_file.cpp creator_by_file.hpp)
