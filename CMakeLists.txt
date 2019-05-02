cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/interface.cpp
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
)


add_executable(RLBotCPP main.cpp ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)
