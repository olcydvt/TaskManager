#include <mutex>
#include <iostream>

#include "State.h"
#include "../task_dir/Task.h"

class AbortState : public State {
public:

    explicit AbortState(Task& in_task) :task(in_task) {}

    void start() override {
        return;
    }

    void abort() override {
        return;
    }
    void pause() override {
        std::unique_lock<std::mutex> lock(task.m_jobMutex);
        state = "idle";
        task.conditions.resume_cv.wait(lock, [this]() {return task.atomics.isResuming.load(); });
        task.atomics.isResuming = false;

    }
    void resume() override {
        return;
    }
    Task& task;
};
