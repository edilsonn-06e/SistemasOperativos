
#include "PRIORITY.h"
#include <algorithm>

std::vector<Process> PRIORITY::run() {
    // Non-preemptive priority (menor valor = mayor prioridad)
    std::sort(processes.begin(), processes.end(), [](auto&a, auto&b){
        if (a.arrivalTime == b.arrivalTime) return a.priority < b.priority;
        return a.arrivalTime < b.arrivalTime;
    });
    int t = 0;
    std::vector<Process> done;
    std::vector<bool> used(processes.size(), false);
    int finished = 0;
    while (finished < (int)processes.size()) {
        int pick = -1;
        for (int i=0;i<(int)processes.size();++i) {
            if (used[i]) continue;
            if (processes[i].arrivalTime <= t) {
                if (pick==-1 || processes[i].priority < processes[pick].priority) pick = i;
            }
        }
        if (pick==-1) { t++; continue; }
        auto p = processes[pick];
        used[pick] = true; finished++;
        p.startTime = t;
        t += p.burstTime;
        p.finishTime = t;
        p.waitingTime = p.finishTime - p.arrivalTime - p.burstTime;
        p.turnaroundTime = p.finishTime - p.arrivalTime;
        p.responseTime = p.startTime - p.arrivalTime;
        done.push_back(p);
    }
    return done;
}
