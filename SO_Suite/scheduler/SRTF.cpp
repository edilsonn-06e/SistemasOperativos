#include "SRTF.h"
#include <QDebug>

void SRTF::addProcess(const Process &p) {
    processes.push_back(p);
}

std::vector<Process> SRTF::run() {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    std::vector<Process*> ready;
    Process* current = nullptr;

    qDebug() << "---- Ejecutando SRTF ----";

    while (completed < n) {
        // Añadir procesos que llegan al tiempo actual
        for (auto &p : processes) {
            if (p.arrivalTime == currentTime && p.state == ProcState::NEW) {
                p.state = ProcState::READY;
                ready.push_back(&p);
            }
        }

        // Seleccionar el proceso con menor tiempo restante
        if (!ready.empty()) {
            current = *std::min_element(ready.begin(), ready.end(),
                                        [](Process* a, Process* b) { return a->remainingTime < b->remainingTime; });

            current->state = ProcState::RUNNING;
            qDebug() << "t=" << currentTime << "-> Ejecutando PID:" << current->pid;

            current->remainingTime--;

            if (current->remainingTime == 0) {
                current->state = ProcState::TERMINATED;
                ready.erase(std::remove(ready.begin(), ready.end(), current), ready.end());
                completed++;
            } else {
                current->state = ProcState::READY;
            }
        }

        currentTime++;
    }

    qDebug() << "---- Finalizado SRTF ----";
    return processes;
}
