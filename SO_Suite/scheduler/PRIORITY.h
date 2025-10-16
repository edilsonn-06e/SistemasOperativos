#pragma once
#include "Scheduler.h"
#include <algorithm>

class PRIORITY : public Scheduler {
private:
    std::vector<Process> processes;

public:
    void addProcess(const Process &p) override;
    std::vector<Process> run() override;
};
