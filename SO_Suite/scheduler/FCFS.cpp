#include "FCFS.h"
#include <QDebug>
#include <algorithm>

void FCFS::addProcess(const Process &p) {
    queue.push_back(p);
}

std::vector<Process> FCFS::run() {
    // 1) Orden por llegada
    std::sort(queue.begin(), queue.end(),
              [](const Process &a, const Process &b) {
                  return a.arrivalTime < b.arrivalTime;
              });

    int currentTime = 0;

    for (auto &p : queue) {
        // 2) Si hay inactividad, saltar al tiempo de llegada
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;

        // 3) Calcular métricas
        p.startTime      = currentTime;
        p.finishTime     = p.startTime + p.burstTime;
        p.waitingTime    = p.startTime - p.arrivalTime;
        p.turnaroundTime = p.finishTime - p.arrivalTime;
        p.responseTime   = p.startTime - p.arrivalTime;

        qDebug() << "[FCFS] PID:" << p.pid
                 << "Inicio:" << p.startTime
                 << "Fin:" << p.finishTime
                 << "WT:" << p.waitingTime
                 << "TAT:" << p.turnaroundTime
                 << "RT:" << p.responseTime;

        currentTime = p.finishTime;
        p.state = ProcState::TERMINATED;
    }

    return queue; // Devuelve métricas completas
}
