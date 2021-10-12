#include <iostream>
#include <string>
#include <map>
#include <sstream>


using namespace std;

class CLIManager {
public:
	CLIManager(TaskManager& in_taskManager)
	:m_taskManager(in_taskManager) {
		

		std::cout << "---Control commands for application inputs---"
			<< "\n"
			<< "status - returns ids and status of all registered jobs"
			<< "\n"
			<< "start <id> - starts job with the given id"
			<< "\n"
			<< "abort <id> - aborts execution of a job with the given id"
			<< "\n"
			<< "pause <id> - aborts execution of a job with the given id"
			<< "\n"
			<< "resume <id> - aborts execution of a job with the given id"
			<< "\n"
			<< "quit <id> - aborts execution of a job with the given id"
			<< "\n"
			<< "\n";
	}

	void runCLI() {
		string cmd{};
		cout << "Enter your command: " << "\n";
		std::getline(std::cin, cmd);

		if (cmd.empty()) {
			cout << "Please run proper command for example: start _id" << "\n";
			return;
		}

		vector<string> strings;
		std::istringstream tokenStream(cmd);
		std::string token;

		while (getline(tokenStream, token, ' ')) {
			strings.push_back(token);
		}

		if (strings.size() < 0 || strings.size() >2) {
			cout << "Please run proper command for example: start _id" << "\n";
			return;
		}

		cout << cmd << " will be executed " << "\n";

		const auto& key = strings[0];
		switch (cmdMap[key])
		{
			case 0:
				m_taskManager.start( stoi(strings[1]) );
				break;
			case 1:
				m_taskManager.abort(stoi(strings[1]));
				break;
			case 2:
				m_taskManager.pause(stoi(strings[1]));
				break;
			case 3:
				m_taskManager.resume(stoi(strings[1]));
				break;
			case 4:
				break;
			case 5:
				m_taskManager.getJobState();
				break;
			default:
				break;
		}
	}

private:
	std::map<std::string, int> cmdMap{ {"start", 0}, {"abort", 1}, {"pause", 2}, {"resume", 3}, {"quit", 4}, {"status", 5} };
	TaskManager& m_taskManager;

};