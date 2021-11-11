#include <mutex>
#include <iostream>
#include "State.h"
#include "../task_dir/Task.h"

class StartState : public State {
public:
    
    explicit StartState(Task& in_task) :task(in_task) {
        state = "idle";
    }

    void start() override {
        
        {
            std::unique_lock<std::mutex> lock(task.m_jobMutex);
            task.conditions.start_cv.wait(lock, [this]() {return task.atomics.isStarting.load(); });
            state = "started";
        }

        //actual job is executedpa
        while(task.atomics.isStarting)
            task.m_job->execute();
    }

    void abort() override {
        return;
    }
    void pause() override {
        return;
    }
    void resume() override {
        return;
    }
    Task& task;
};
