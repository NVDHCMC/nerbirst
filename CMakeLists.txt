cmake_minimum_required(VERSION 2.4)
project(nerbist)

file(GLOB SRCS src/*.cc)

include_directories(./inc)

message(${SRCS})
add_executable(${PROJECT_NAME}_executable ${SRCS})
target_link_libraries(${PROJECT_NAME}_executable)