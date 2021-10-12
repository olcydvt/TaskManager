#pragma once

#include <mutex>
#include <iostream>
#include <chrono>

#include "State.h"
#include "Task.h"

class PauseState : public State {
public:

    explicit PauseState(Task& in_task) :task(in_task) {}

    void start() override {
        return;
    }

    void abort() override {
        return;
    }
    void pause() override {

       //ToDo: seperate locks
        std::unique_lock<std::mutex> lock(task.m_jobMutex);
        state = "paused";
        task.conditions.resume_cv.wait(lock, [this]() {return task.atomics.isResuming.load(); });
        task.atomics.isResuming = false;
        
        /*
            using namespace std::chrono_literals;
            auto start = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(100ms);
        */
    }
    void resume() override {
        return;
    }
    Task& task;
};
