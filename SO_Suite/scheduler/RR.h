#pragma once
#include "Scheduler.h"
#include <queue>

class RR : public Scheduler {
private:
    std::vector<Process> processes;
    int quantum;

public:
    explicit RR(int q = 2) : quantum(q) {}  // valor por defecto = 2
    void addProcess(const Process &p) override;
    std::vector<Process> run() override;
};
