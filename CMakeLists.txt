cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/bot.cc
  ${PROJECT_SOURCE_DIR}/src/color.cc
  ${PROJECT_SOURCE_DIR}/src/interface.cc
  ${PROJECT_SOURCE_DIR}/src/matchsettings.cc
  ${PROJECT_SOURCE_DIR}/src/namedrenderer.cc
  ${PROJECT_SOURCE_DIR}/src/platform_linux.cc
  ${PROJECT_SOURCE_DIR}/src/platform_windows.cc
  ${PROJECT_SOURCE_DIR}/src/renderer.cc
  ${PROJECT_SOURCE_DIR}/src/scopedrenderer.cc
  ${PROJECT_SOURCE_DIR}/src/server.cc
  ${PROJECT_SOURCE_DIR}/src/sockets_linux.cc
  ${PROJECT_SOURCE_DIR}/src/sockets_windows.cc
  ${PROJECT_SOURCE_DIR}/src/statesetting.cc
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/bot.h
  ${PROJECT_SOURCE_DIR}/inc/botmanager.h
  ${PROJECT_SOURCE_DIR}/inc/color.h
  ${PROJECT_SOURCE_DIR}/inc/controller.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
  ${PROJECT_SOURCE_DIR}/inc/matchsettings.h
  ${PROJECT_SOURCE_DIR}/inc/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/platform.h
  ${PROJECT_SOURCE_DIR}/inc/renderer.h
  ${PROJECT_SOURCE_DIR}/inc/scopedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/server.h
  ${PROJECT_SOURCE_DIR}/inc/sockets.h
  ${PROJECT_SOURCE_DIR}/inc/statesetting.h
)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)
target_compile_features(RLBotCPP PRIVATE cxx_std_17)