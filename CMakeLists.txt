cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/interface.cpp
)

add_executable(RLBotCPP main.cpp ${source_files})
target_include_directories(RLBotCPP PUBLIC inc/)