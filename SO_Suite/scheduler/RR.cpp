#include "RR.h"
#include <QDebug>
#include <algorithm>

void RR::addProcess(const Process &p) {
    processes.push_back(p);
}

std::vector<Process> RR::run() {
    qDebug() << "---- Ejecutando RR (Quantum =" << quantum << ") ----";

    std::sort(processes.begin(), processes.end(),
              [](const Process &a, const Process &b) { return a.arrivalTime < b.arrivalTime; });

    int currentTime = 0;
    std::queue<int> ready;
    int n = processes.size();
    int completed = 0;
    std::vector<bool> inQueue(n, false);

    // timeline de ejecución
    while (completed < n) {
        // agregar procesos recién llegados
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !inQueue[i] && processes[i].state != ProcState::TERMINATED) {
                ready.push(i);
                inQueue[i] = true;
                processes[i].state = ProcState::READY;
            }
        }

        if (ready.empty()) {
            currentTime++;
            continue;
        }

        int idx = ready.front();
        ready.pop();
        inQueue[idx] = false;

        Process &p = processes[idx];

        if (p.state == ProcState::NEW || p.state == ProcState::READY)
            p.state = ProcState::RUNNING;

        if (p.remainingTime == p.burstTime)
            p.startTime = currentTime;

        qDebug() << "t=" << currentTime << "-> PID:" << p.pid << "(rem" << p.remainingTime << ")";

        int execTime = std::min(quantum, p.remainingTime);
        p.remainingTime -= execTime;
        currentTime += execTime;

        // agregar procesos que llegaron durante la ejecución
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !inQueue[i] && processes[i].state != ProcState::TERMINATED && i != idx) {
                ready.push(i);
                inQueue[i] = true;
                processes[i].state = ProcState::READY;
            }
        }

        if (p.remainingTime == 0) {
            p.finishTime = currentTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            p.responseTime = p.startTime - p.arrivalTime;
            p.state = ProcState::TERMINATED;
            completed++;
        } else {
            ready.push(idx);
            inQueue[idx] = true;
            p.state = ProcState::READY;
        }
    }

    qDebug() << "---- Finalizado RR ----";

    for (auto &p : processes) {
        qDebug() << "[RR] PID:" << p.pid
                 << "Inicio:" << p.startTime
                 << "Fin:" << p.finishTime
                 << "WT:" << p.waitingTime
                 << "TAT:" << p.turnaroundTime
                 << "RT:" << p.responseTime;
    }

    return processes;
}
