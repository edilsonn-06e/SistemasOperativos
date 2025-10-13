#pragma once
#include "Scheduler.h"
#include <algorithm>

class FCFS : public Scheduler {
private:
    std::vector<Process> queue;   // Cola de procesos
public:
    void addProcess(const Process &p) override;  // Agrega proceso a la cola
    std::vector<Process> run() override;         // Ejecuta FCFS
};
