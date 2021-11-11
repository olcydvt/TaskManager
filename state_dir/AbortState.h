
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
        state = "aborted";
        throw std::runtime_error("task is aborted");
    }
    void pause() override {
        return;

    }
    void resume() override {
        return;
    }
    Task& task;
};
