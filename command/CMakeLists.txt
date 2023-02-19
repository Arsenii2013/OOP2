cmake_minimum_required(VERSION 3.24)
project(command)

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
add_executable(test test.cpp command.hpp text_processor.hpp factory.hpp command_stack.hpp insert.hpp delete.hpp copy.hpp paste.hpp clipboard.hpp parser.hpp service_command.hpp service_command_factory.hpp text_editor.hpp command_dto.hpp clipboard.cpp command_stack.cpp copy.cpp delete.cpp factory.cpp insert.cpp parser.cpp paste.cpp redo.cpp redo.hpp undo.cpp undo.hpp text_editor.cpp text_processor.cpp command_names.hpp service_command_factory.cpp copy_parser.cpp copy_parser.hpp paste_parser.cpp paste_parser.hpp insert_parser.cpp insert_parser.hpp delete_parser.cpp delete_parser.hpp interval.hpp interval.cpp)
target_link_libraries(test gtest_main)

add_executable(command main.cpp command.hpp text_processor.hpp factory.hpp command_stack.hpp insert.hpp delete.hpp copy.hpp paste.hpp clipboard.hpp parser.hpp service_command.hpp service_command_factory.hpp text_editor.hpp command_dto.hpp clipboard.cpp command_stack.cpp copy.cpp delete.cpp factory.cpp insert.cpp parser.cpp paste.cpp redo.cpp redo.hpp undo.cpp undo.hpp text_editor.cpp text_processor.cpp command_names.hpp service_command_factory.cpp copy_parser.cpp copy_parser.hpp paste_parser.cpp paste_parser.hpp insert_parser.cpp insert_parser.hpp delete_parser.cpp delete_parser.hpp interval.hpp interval.cpp)
