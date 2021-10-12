#include "Task.h"
#include "StartState.h"
#include "PauseState.h"
#include "AbortState.h"



Task::Task() {
    startState = std::make_shared<StartState>(*this);
    pauseState = std::make_shared<PauseState>(*this);
    abortState = std::make_shared<AbortState>(*this);

    setState(startState);
}

void Task::execute() {
    while (true)
    {
        currentState->start();
        try {
            currentState->abort();
        } catch (std::exception& e) {
            std::cout << e.what() << "\n";
            return;
        }
            
        currentState->pause();
        currentState->resume();
    }
}

void Task::setState(const std::shared_ptr<State>& state) {
    currentState = state;
}





