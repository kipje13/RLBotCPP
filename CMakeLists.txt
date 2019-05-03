cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/bot.cpp
  ${PROJECT_SOURCE_DIR}/src/botmanager.cpp
  ${PROJECT_SOURCE_DIR}/src/interface.cpp
  ${PROJECT_SOURCE_DIR}/src/namedrenderer.cpp
  ${PROJECT_SOURCE_DIR}/src/renderer.cpp
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/bot.h
  ${PROJECT_SOURCE_DIR}/inc/botmanager.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
  ${PROJECT_SOURCE_DIR}/inc/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/renderer.h
)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)

add_executable(CPPExampleBot main.cpp examplebot.cpp examplebot.h)
target_link_libraries(CPPExampleBot RLBotCPP)
target_include_directories(CPPExampleBot PRIVATE inc lib/inc)