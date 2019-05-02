cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
${PROJECT_SOURCE_DIR}/src/bot.cpp
  ${PROJECT_SOURCE_DIR}/src/interface.cpp
  ${PROJECT_SOURCE_DIR}/src/namedrenderer.cpp
  ${PROJECT_SOURCE_DIR}/src/renderer.cpp
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h

  ${PROJECT_SOURCE_DIR}/inc/bot.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
  ${PROJECT_SOURCE_DIR}/inc/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/renderer.h
)


add_executable(RLBotCPP main.cpp ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)