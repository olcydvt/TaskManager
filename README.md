# Task Manager

> **Version:** 0.1.0 **Date:** 12.10.2021 **Author:** Olcay Davut Cabbas
>
> **Email:** [olcay.d.cabbas@gmail.com]

### Requirements
A compiler supporting the C++17 features.

## Features

	List of features included in
 
	Implement a manager that controls execution of tasks running as parallel jobs. Give example
	implementation of 2 time-consuming tasks that may be run as jobs by the manager.
	At program startup, the task manager registers as many jobs as it is indicated by the input parameter N.
	The registration of a job is defined as assignment of a task (function to run) to an execution thread
	managed by the task manager. Each of two example tasks can be registered multiple times (to fulfill the
	requirement of N running jobs), and each registration yields a unique job id. The tasks are considered
	independent, in a way that they do not share data.
	The manager should run within a console application and accept control commands from a command
	prompt.
	Application input: N – number of jobs to run.
	Control commands:


	* status – returns ids and status of all registered jobs.
		** The job status can be one of the following: idle/running/paused/aborted
	* start <id> - starts job with the given id
	* abort <id> - aborts execution of a job with the given id
	* pause <id> - halts execution of a job with the given id
	* resume <id> - resumes execution of a halted job
	* quit – aborts all running jobs and quits the application

## Cmake

 * mkdir build
 * cd build
 * cmake ../

## UML
![Class Diagram](https://github.com/olcydvt/TaskManager/blob/master/UML.PNG?raw=true "Title")


### Basic Usage
###### Client side
```C++
	auto testFunc2 = []() {
		using namespace std::chrono_literals;
		//std::cout << "testFunc is running" << "\n";
		std::this_thread::sleep_for(1000ms);
		return;
	};

	auto numOfThread = 4;
	TaskManager taskManager(numOfThread);
	// Assign job to a worker thread.
	taskManager.assignTask(testFunc, 3);
```