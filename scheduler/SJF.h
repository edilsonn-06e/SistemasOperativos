
#pragma once
#include "Scheduler.h"

class SJF : public Scheduler {
    std::vector<Process> processes;
public:
    void addProcess(const Process& p) override { processes.push_back(p); }
    std::vector<Process> run() override;
};
