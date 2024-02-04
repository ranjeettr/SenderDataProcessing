cmake_minimum_required(VERSION 3.13.4)

project(processmessages)


set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} receiver sender buffer)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_TOP_DIR}/Buffer/ ${CMAKE_TOP_DIR}/Sender/ ${CMAKE_TOP_DIR}/Receiver/)
add_subdirectory(Buffer)
add_subdirectory(Sender)
add_subdirectory(Receiver)
