
add_library(states INTERFACE
	#State.h
	#StartState.h
	#PauseState.h
	#IdleState.h
	#AbortState.h
	)

target_include_directories(states INTERFACE .)
