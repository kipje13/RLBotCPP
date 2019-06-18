cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/bot.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/botmanager.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/interface.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/matchsettings.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/namedrenderer.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/renderer.cc
        ${PROJECT_SOURCE_DIR}/rlbot-src/src/statesetting.cc
)

set(header_files
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/rlbot_generated.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/bot.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/botmanager.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/errorcodes.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/interface.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/matchsettings.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/namedrenderer.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/renderer.h
        ${PROJECT_SOURCE_DIR}/rlbot-src/inc/statesetting.h
)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE rlbot-src/inc rlbot-src/lib/inc)
target_compile_features(RLBotCPP PRIVATE cxx_std_17)

add_executable(CPPExampleBot main.cc examplebot.cc examplebot.h)
target_link_libraries(CPPExampleBot RLBotCPP)
target_include_directories(CPPExampleBot PRIVATE rlbot-src/inc rlbot-src/lib/inc)
target_compile_features(CPPExampleBot PRIVATE cxx_std_17)
