
#include "FCFS.h"
#include <algorithm>

std::vector<Process> FCFS::run() {
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b){ return a.arrivalTime < b.arrivalTime; });
    int t = 0;
    for (auto& p : processes) {
        if (t < p.arrivalTime) t = p.arrivalTime;
        p.startTime = t;
        t += p.burstTime;
        p.finishTime = t;
        p.waitingTime = p.finishTime - p.arrivalTime - p.burstTime;
        p.turnaroundTime = p.finishTime - p.arrivalTime;
        p.responseTime = p.startTime - p.arrivalTime;
    }
    return processes;
}
