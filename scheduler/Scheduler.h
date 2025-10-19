
#pragma once
#include "../core/Process.h"
#include <vector>

class Scheduler {
public:
    virtual ~Scheduler() = default;
    virtual void addProcess(const Process& p) = 0;
    virtual std::vector<Process> run() = 0;
};
