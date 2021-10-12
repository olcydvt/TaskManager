cmake_minimum_required (VERSION 2.8.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")

set(PROJECT_NAME "TaskManager")

project (${PROJECT_NAME} CXX)


set(SOURCES main.cpp State.h AbortState.h CLIManager.h IdleState.h PauseState.h StartState.h  Task.h Task.cpp TaskManager.h )

 
add_executable(taskManager ${SOURCES})
target_link_libraries(taskManager pthread)

target_compile_features(taskManager PRIVATE cxx_std_17)



