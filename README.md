# Task Manager

> **Version:** 0.1.0 **Date:** 12.10.2021 **Author:** Olcay Davut Cabbas
>
> **Email:** [olcay.d.cabbas@gmail.com]

### Requirements
A compiler supporting the C++17 features.

## Features

 List of features included in

* status – returns ids and status of all registered jobs.
	** The job status can be one of the following: idle/running/paused/aborted
* start <id> - starts job with the given id
* abort <id> - aborts execution of a job with the given id
* pause <id> - halts execution of a job with the given id
* resume <id> - resumes execution of a halted job
* quit – aborts all running jobs and quits the application

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