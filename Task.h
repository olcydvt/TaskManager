
#ifndef TASK_H
#define TASK_H

#include <atomic>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <utility>
#include <iostream>
#include <string>

#include "State.h"

class Task {
public:
    Task();
    void setState(const std::shared_ptr<State>& state);

    template <typename Func, typename... Args >
    auto setJob(Func&& f, Args&&... args) {
        using retType = decltype(f(args...));

        //package the task
        std::function<retType()> task(std::move(std::bind(f, args...)));

        std::lock_guard<std::mutex> lock(m_jobMutex);

        m_job = std::make_shared<AnyJob<retType> >(std::move(task));
    
    }
    void execute();

    const std::string& getCurrentStatus() const {
        return currentState->getCurrentState();
    }


    std::shared_ptr<State> getPauseState() {
        return pauseState;
    }

    std::shared_ptr<State> getStartState() {
        return startState;
    }

    std::shared_ptr<State> getAbortState() {
        return abortState;
    }

    class Job {
    public:
        virtual ~Job() {}
        virtual void execute() = 0;
    };

    template <typename RetType>
    class AnyJob : public Job {
    private:
        //std::packaged_task<RetType()> func;
        std::function<RetType()> func;
    public:
        AnyJob(std::function<RetType()> func) : func(std::move(func)) {}
        void execute() {
            func();
        }
        ~AnyJob() {
            std::cout << "job is deleted";
        }
    };

    struct Conditions {
        std::condition_variable start_cv;
        std::condition_variable abort_cv;
        std::condition_variable pause_cv;
        std::condition_variable resume_cv;
    };
    Conditions conditions;
    std::shared_ptr<Job > m_job;
    std::mutex m_jobMutex;

    struct Atomics {
        std::atomic_bool isStarting{ false };
        std::atomic_bool isPausing{ false };
        std::atomic_bool isResuming{ false };
    };

    Atomics atomics;


private:
    std::shared_ptr<State> startState;
    std::shared_ptr<State> pauseState;
    std::shared_ptr<State> abortState;
    std::shared_ptr<State> currentState;
};


#endif //TASK_H
