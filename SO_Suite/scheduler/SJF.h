#pragma once
#include "Scheduler.h"
#include <algorithm>

class SJF : public Scheduler {
private:
    std::vector<Process> queue;
public:
    void addProcess(const Process &p) override;
    std::vector<Process> run() override;
};
