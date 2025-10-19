
#include "SRTF.h"
#include <algorithm>
#include <limits>

std::vector<Process> SRTF::run() {
    auto procs = processes;
    for (auto& p : procs) p.remainingTime = p.burstTime;
    int completed = 0;
    int t = 0;
    int lastPid = -1;
    while (completed < (int)procs.size()) {
        int pick = -1, bestRem = std::numeric_limits<int>::max();
        for (int i=0;i<(int)procs.size();++i) {
            if (procs[i].arrivalTime <= t && procs[i].remainingTime > 0) {
                if (procs[i].remainingTime < bestRem) {
                    bestRem = procs[i].remainingTime;
                    pick = i;
                }
            }
        }
        if (pick==-1) { t++; continue; }
        if (procs[pick].startTime == -1) procs[pick].startTime = t;
        procs[pick].remainingTime--;
        t++;
        if (procs[pick].remainingTime == 0) {
            procs[pick].finishTime = t;
            procs[pick].waitingTime = procs[pick].finishTime - procs[pick].arrivalTime - procs[pick].burstTime;
            procs[pick].turnaroundTime = procs[pick].finishTime - procs[pick].arrivalTime;
            procs[pick].responseTime = procs[pick].startTime - procs[pick].arrivalTime;
            completed++;
        }
    }
    return procs;
}
