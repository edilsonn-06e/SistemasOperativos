#include "SRTF.h"
#include <QDebug>
#include <algorithm>

void SRTF::addProcess(const Process &p) {
    processes.push_back(p);
}

std::vector<Process> SRTF::run() {
    // Trabajamos sobre copia local para manipular estados/tiempos
    std::vector<Process> procs = processes;

    int n = static_cast<int>(procs.size());
    int completed = 0;
    int currentTime = 0;

    std::vector<Process*> ready;

    qDebug() << "---- Ejecutando SRTF (expropiativo) ----";

    // Para obtener próximo arrival si ready está vacío
    auto nextArrivalTime = [&]() -> int {
        int t = INT_MAX;
        for (auto &p : procs) {
            if (p.state == ProcState::NEW)
                t = std::min(t, p.arrivalTime);
        }
        return t == INT_MAX ? currentTime : t;
    };

    while (completed < n) {
        // 1) Mover a ready los que llegan en t actual
        for (auto &p : procs) {
            if (p.state == ProcState::NEW && p.arrivalTime <= currentTime) {
                p.state = ProcState::READY;
            }
        }

        // Construir lista de punteros listos
        ready.clear();
        for (auto &p : procs) {
            if (p.state == ProcState::READY || p.state == ProcState::RUNNING) {
                if (p.remainingTime > 0)
                    ready.push_back(&p);
            }
        }

        if (ready.empty()) {
            // No hay listos: saltar al próximo arrival
            int jump = nextArrivalTime();
            if (jump > currentTime) currentTime = jump;
            continue;
        }

        // 2) Elegir el de menor remainingTime (desempate por arrivalTime, luego PID)
        auto cmp = [](Process* a, Process* b) {
            if (a->remainingTime != b->remainingTime)
                return a->remainingTime < b->remainingTime;
            if (a->arrivalTime != b->arrivalTime)
                return a->arrivalTime < b->arrivalTime;
            return a->pid < b->pid;
        };
        Process* current = *std::min_element(ready.begin(), ready.end(), cmp);

        // 3) Marcar startTime si es su primera CPU
        if (current->startTime == -1) {
            current->startTime = currentTime;
        }

        // 4) Ejecutar 1 unidad
        current->state = ProcState::RUNNING;
        qDebug() << "t=" << currentTime << "-> PID:" << current->pid
                 << "(rem" << current->remainingTime << ")";
        current->remainingTime--;

        // 5) Si terminó, calcular métricas y marcar
        if (current->remainingTime == 0) {
            current->finishTime     = currentTime + 1; // terminó al final de esta unidad
            current->turnaroundTime = current->finishTime - current->arrivalTime;
            current->waitingTime    = current->turnaroundTime - current->burstTime;
            current->responseTime   = current->startTime - current->arrivalTime;
            current->state = ProcState::TERMINATED;
            completed++;
        } else {
            // Vuelve a READY para una posible expropiación
            current->state = ProcState::READY;
        }

        // 6) Avanzar tiempo
        currentTime++;
    }

    qDebug() << "---- Finalizado SRTF ----";
    return procs;
}
