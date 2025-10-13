#include "FCFS.h"
#include <QDebug>
#include <algorithm>

void FCFS::addProcess(const Process &p) {
    queue.push_back(p);
}

std::vector<Process> FCFS::run() {
    std::sort(queue.begin(), queue.end(),
              [](const Process &a, const Process &b) {
                  return a.arrivalTime < b.arrivalTime;
              });

    int currentTime = 0;
    for (auto &p : queue) {
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;

        qDebug() << "Ejecutando PID:" << p.pid
                 << "Ráfaga:" << p.burstTime
                 << "desde t=" << currentTime;

        currentTime += p.burstTime;
        p.state = ProcState::TERMINATED;
    }

    return queue;
}
