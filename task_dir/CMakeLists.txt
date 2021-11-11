add_library(tskmngr
	Task.cpp
	Task.h
	TaskManager.h)

target_include_directories(tskmngr PUBLIC . ../state_dir)
