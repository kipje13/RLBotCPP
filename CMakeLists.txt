cmake_minimum_required(VERSION 3.8)
project(RLBotCPP LANGUAGES CXX)

set(source_files
  ${PROJECT_SOURCE_DIR}/src/bot.cc
  ${PROJECT_SOURCE_DIR}/src/botmanager.cc
  ${PROJECT_SOURCE_DIR}/src/interface.cc
  ${PROJECT_SOURCE_DIR}/src/matchsettings.cc
  ${PROJECT_SOURCE_DIR}/src/namedrenderer.cc
  ${PROJECT_SOURCE_DIR}/src/renderer.cc
  ${PROJECT_SOURCE_DIR}/src/statesetting.cc
)

set(header_files
  ${PROJECT_SOURCE_DIR}/inc/rlbot_generated.h
  ${PROJECT_SOURCE_DIR}/inc/bot.h
  ${PROJECT_SOURCE_DIR}/inc/botmanager.h
  ${PROJECT_SOURCE_DIR}/inc/errorcodes.h
  ${PROJECT_SOURCE_DIR}/inc/interface.h
  ${PROJECT_SOURCE_DIR}/inc/matchsettings.h
  ${PROJECT_SOURCE_DIR}/inc/namedrenderer.h
  ${PROJECT_SOURCE_DIR}/inc/renderer.h
  ${PROJECT_SOURCE_DIR}/inc/statesetting.h
)

add_library(RLBotCPP STATIC ${source_files} ${header_files})
target_include_directories(RLBotCPP PRIVATE inc lib/inc)
target_compile_features(RLBotCPP PRIVATE cxx_std_17)

add_executable(CPPExampleBot main.cc examplebot.cc examplebot.h)
target_link_libraries(CPPExampleBot RLBotCPP)
target_include_directories(CPPExampleBot PRIVATE inc lib/inc)
target_compile_features(CPPExampleBot PRIVATE cxx_std_17)

add_custom_command(TARGET  CPPExampleBot POST_BUILD
    COMMAND python ${PROJECT_SOURCE_DIR}/dlls/copy-dlls.py)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_custom_command(TARGET CPPExampleBot POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/dlls/RLBot_Core_Interface.dll"
        $<TARGET_FILE_DIR:CPPExampleBot>)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_custom_command(TARGET CPPExampleBot POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/dlls/RLBot_Core_Interface_32.dll"
        $<TARGET_FILE_DIR:CPPExampleBot>)
endif()