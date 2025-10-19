
#pragma once
#include <vector>

enum class ProcState { NEW, READY, RUNNING, WAITING, TERMINATED };

struct Process {
    int pid = 0;
    int arrivalTime = 0;
    int burstTime = 0;
    int priority = 0;
    int remainingTime = 0;
    ProcState state = ProcState::NEW;

    int startTime = -1;
    int finishTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int responseTime = 0;

    Process() = default;
    Process(int id, int arrival, int burst, int prio = 0)
        : pid(id), arrivalTime(arrival), burstTime(burst), priority(prio), remainingTime(burst) {}
};
