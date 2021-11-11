cmake_minimum_required (VERSION 2.8.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")

set(PROJECT_NAME "TaskManager")

project (${PROJECT_NAME} CXX)

add_subdirectory(cli_dir)
add_subdirectory(task_dir)
add_subdirectory(state_dir)


set(SOURCES main.cpp)

 
add_executable(taskManager ${SOURCES})
target_link_libraries(taskManager PRIVATE pthread states tskmngr cli)


