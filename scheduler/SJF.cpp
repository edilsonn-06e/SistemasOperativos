
#include "SJF.h"
#include <algorithm>

std::vector<Process> SJF::run() {
    // Non-preemptive SJF
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b){ return a.arrivalTime < b.arrivalTime; });
    int t = 0;
    std::vector<Process> done;
    std::vector<bool> used(processes.size(), false);
    int finished = 0;
    while (finished < (int)processes.size()) {
        // pick available shortest burst
        int pick = -1;
        for (int i=0;i<(int)processes.size();++i) {
            if (used[i]) continue;
            if (processes[i].arrivalTime <= t) {
                if (pick==-1 || processes[i].burstTime < processes[pick].burstTime) pick = i;
            }
        }
        if (pick==-1) { t = processes[finished].arrivalTime; continue; }
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
