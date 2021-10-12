#pragma once

#include <vector>
#include <map>
#include "Task.h"

class TaskManager {
public:
    explicit TaskManager(int in_numOfThreads)
    : numOfThreads(in_numOfThreads){
        threadPool.reserve(numOfThreads);
    };

    ~TaskManager() {
        std::cout << "TaskManager destructor" << "\n";
        for (auto& th : threadPool) {
            if (th.joinable()) {
                th.join();
            }
        }
    }

    using jobId = int;
    struct TaskPackage
    {
        TaskPackage(jobId id, std::shared_ptr<Task>& in_task)
        :_uniqueJobId(id)
        , _task(in_task){
        }

        jobId _uniqueJobId;
        std::shared_ptr<Task> _task;
    };

    template <typename Func, typename... Args >
    auto assignTask(Func&& f, Args&&... args) {
        auto task = std::make_shared<Task>();
        task->setJob(f, std::forward<Args>(args)... );

        threadPool.emplace_back(std::thread(&Task::execute, task));

        jobId uniqueJobId = rand() % numOfThreads + 1;
        std::cout << "created job Id: " << uniqueJobId << "\n" << "\n";

        auto taskPackage = std::make_shared<TaskPackage>(uniqueJobId , task);
        taskPackageMap[uniqueJobId] = taskPackage;
        return uniqueJobId;
    }

    void start(jobId _uniqueJobId) {
        if (auto task = taskPackageMap[_uniqueJobId]; task != nullptr) {
            task->_task->atomics.isStarting = true;
            auto& cv = task->_task->conditions.start_cv;
            cv.notify_one();
        }
        
    }

    void abort(jobId _uniqueJobId) {
        if (auto task = taskPackageMap[_uniqueJobId]; task != nullptr) {
            auto pTask = task->_task;
            pTask->setState(pTask->getAbortState());
            task->_task->atomics.isStarting = false;
        }
    }

    void pause(jobId _uniqueJobId) {
        if (auto task = taskPackageMap[_uniqueJobId]; task != nullptr) {
            auto pTask = task->_task;
            pTask->setState(pTask->getPauseState());
            task->_task->atomics.isStarting = false;
        }
    }


    void resume(jobId _uniqueJobId) {
        if (auto task = taskPackageMap[_uniqueJobId]; task != nullptr) {
            auto pTask = task->_task;
            pTask->setState(pTask->getStartState());

            pTask->atomics.isResuming = true;
            pTask->conditions.resume_cv.notify_one();
      
            pTask->atomics.isStarting = true;
            pTask->conditions.start_cv.notify_one();
        }
    }

    void getJobState()  {
        for (auto& task : taskPackageMap) {
            auto pTask = task.second->_task;
            std::cout << "status of job Id " << task.first << ": " << pTask->getCurrentStatus() << "\n";
        }
    }

    void quit() {
        //todo
    }


private:

	/**
	* Thread to be executed with Task object
	*/
    std::unordered_map<jobId, std::shared_ptr<TaskPackage> > taskPackageMap;
    std::vector<std::thread > threadPool;

    std::thread thread;
    int numOfThreads{ 0 };

	

};
