#include "SJF.h"
#include <QDebug>
#include <algorithm>

void SJF::addProcess(const Process &p) {
    queue.push_back(p);
}

std::vector<Process> SJF::run() {
    // Ordenar por tiempo de llegada, luego por ráfaga
    std::sort(queue.begin(), queue.end(),
              [](const Process &a, const Process &b) {
                  if (a.arrivalTime == b.arrivalTime)
                      return a.burstTime < b.burstTime;
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
