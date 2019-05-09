cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/bot.cc
  ${PROJECT_SOURCE_DIR}/src/botmanager.cc
  ${PROJECT_SOURCE_DIR}/src/statesetting.cc
  ${PROJECT_SOURCE_DIR}/src/interface.cc
  ${PROJECT_SOURCE_DIR}/src/namedrenderer.cc
  ${PROJECT_SOURCE_DIR}/src/renderer.cc
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/bot.h
  ${PROJECT_SOURCE_DIR}/inc/botmanager.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/statesetting.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
  ${PROJECT_SOURCE_DIR}/inc/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/renderer.h
)

add_subdirectory(../RLUtilities/rlutilities/cpp ${build_dir}/rlu)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)
target_compile_features(RLBotCPP PRIVATE cxx_std_17)
target_link_libraries(RLBotCPP PUBLIC rlutilities_cpp)

add_executable(CPPExampleBot main.cc examplebot.cc examplebot.h)
target_link_libraries(CPPExampleBot RLBotCPP)
target_include_directories(CPPExampleBot PRIVATE inc lib/inc)
target_compile_features(CPPExampleBot PRIVATE cxx_std_17)
