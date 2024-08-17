cmake_minimum_required(VERSION 3.16)
project(RLBOTCPP)

add_subdirectory(3rd-party)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/FlatBuffer/rlbot_generated.h 
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/flatbuffers-schema/flatc --gen-all --cpp --gen-object-api --gen-onefile -o ${CMAKE_CURRENT_SOURCE_DIR}/FlatBuffer ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/flatbuffers-schema/rlbot.fbs)
 

add_executable(rlbotcpp main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/FlatBuffer/rlbot_generated.h)
target_include_directories(rlbotcpp PUBLIC ./FlatBuffer)
target_link_libraries(rlbotcpp PRIVATE flatbuffers)