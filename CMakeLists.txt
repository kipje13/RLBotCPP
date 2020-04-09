cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/bot.cc
  ${PROJECT_SOURCE_DIR}/src/botmanager.cc
  ${PROJECT_SOURCE_DIR}/src/botprocess.cc
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
  ${PROJECT_SOURCE_DIR}/inc/rlbot/rlbot.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/bot.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/botmanager.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/botprocess.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/color.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/controller.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/flatbuffercontainer.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/interface.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/matchsettings.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/packets.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/platform.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/renderer.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/scopedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/server.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/sockets.h
  ${PROJECT_SOURCE_DIR}/inc/rlbot/statesetting.h
)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PUBLIC inc lib/inc)
target_compile_features(RLBotCPP PUBLIC cxx_std_17)

#link linux libraries
if (UNIX)
    target_link_libraries(RLBotCPP ${CMAKE_DL_LIBS})
endif (UNIX)