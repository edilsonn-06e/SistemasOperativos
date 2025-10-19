
#pragma once
#include "Scheduler.h"
#include <queue>

class RR : public Scheduler {
    std::vector<Process> processes;
    int quantum = 2;
public:
    explicit RR(int q=2) : quantum(q) {}
    void addProcess(const Process& p) override { processes.push_back(p); }
    std::vector<Process> run() override;
};
