cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0042 NEW)

set(PROJECT_NAME "TaskManager")
project (${PROJECT_NAME} CXX)


set(SOURCES *.cpp *.h)
 
 
add_executable(taskManager ${SOURCES})

