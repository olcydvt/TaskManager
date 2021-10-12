#include <iostream>
#include <string>
#include <signal.h>

#include "TaskManager.h"
#include "CLIManager.h"

std::atomic_bool terminated;
void signal_callback_handler(int signum) {
	cout << "Caught signal " << signum << endl;
	// Terminate program
	terminated = true;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "run with valid int parameter" << "\n";
		//return 1;
	}

	auto testFunc = [](int x) {
		using namespace std::chrono_literals;
		//std::cout << "testFunc is running" << "\n";
		std::this_thread::sleep_for(2000ms);
		return x * x;
	};

	auto testFunc2 = []() {
		using namespace std::chrono_literals;
		//std::cout << "testFunc is running" << "\n";
		std::this_thread::sleep_for(1000ms);
		return;
	};

	//auto numOfThread = std::stoi(argv[1]);
	auto numOfThread = 4;
	TaskManager taskManager(numOfThread);
	taskManager.assignTask(testFunc, 3);
	taskManager.assignTask(testFunc2);

	CLIManager cliManager(taskManager);

	while (1)
	{
		cliManager.runCLI();
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10ms);
		if (terminated)
			break;
	}

	return 0;

}