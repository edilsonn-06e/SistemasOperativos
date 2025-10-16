#include "PRIORITY.h"
#include <QDebug>
#include <algorithm>

void PRIORITY::addProcess(const Process &p) {
    processes.push_back(p);
}

std::vector<Process> PRIORITY::run() {
    qDebug() << "---- Ejecutando Prioridades (no expropiativo) ----";

    std::sort(processes.begin(), processes.end(),
              [](const Process &a, const Process &b) {
                  if (a.arrivalTime == b.arrivalTime)
                      return a.priority < b.priority;
                  return a.arrivalTime < b.arrivalTime;
              });

    int currentTime = 0;

    for (auto &p : processes) {
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;

        p.startTime = currentTime;
        p.finishTime = currentTime + p.burstTime;
        p.turnaroundTime = p.finishTime - p.arrivalTime;
        p.waitingTime = p.startTime - p.arrivalTime;
        p.responseTime = p.startTime - p.arrivalTime;
        p.state = ProcState::TERMINATED;

        qDebug() << "PID:" << p.pid << "Prioridad:" << p.priority
                 << "Inicio:" << p.startTime
                 << "Fin:" << p.finishTime;

        currentTime = p.finishTime;
    }

    qDebug() << "---- Finalizado Prioridades ----";
    return processes;
}
