
#include "RR.h"
#include <algorithm>

std::vector<Process> RR::run() {
    auto procs = processes;
    int n = procs.size();
    for (auto& p : procs) p.remainingTime = p.burstTime;
    std::sort(procs.begin(), procs.end(), [](auto&a, auto&b){return a.arrivalTime < b.arrivalTime;});
    std::queue<int> q;
    int t = 0, i = 0, completed = 0;
    while (completed < n) {
        while (i<n && procs[i].arrivalTime <= t) { q.push(i); i++; }
        if (q.empty()) { t = procs[i].arrivalTime; continue; }
        int idx = q.front(); q.pop();
        auto& p = procs[idx];
        if (p.startTime == -1) p.startTime = t;
        int slice = std::min(quantum, p.remainingTime);
        p.remainingTime -= slice;
        t += slice;
        while (i<n && procs[i].arrivalTime <= t) { q.push(i); i++; }
        if (p.remainingTime > 0) q.push(idx);
        else {
            p.finishTime = t;
            p.waitingTime = p.finishTime - p.arrivalTime - p.burstTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.responseTime = p.startTime - p.arrivalTime;
            completed++;
        }
    }
    return procs;
}
