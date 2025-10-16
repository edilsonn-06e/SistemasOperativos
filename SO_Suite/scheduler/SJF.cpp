#include "SJF.h"
#include <QDebug>
#include <algorithm>

void SJF::addProcess(const Process &p) {
    queue.push_back(p);
}

std::vector<Process> SJF::run() {
    // Trabajaremos sobre una copia local para poder marcar estados
    std::vector<Process> procs = queue;

    // Ordenar por llegada solo para facilitar saltos de tiempo
    std::sort(procs.begin(), procs.end(),
              [](const Process &a, const Process &b) {
                  return a.arrivalTime < b.arrivalTime;
              });

    int n = static_cast<int>(procs.size());
    int done = 0;
    int currentTime = 0;

    // Para elegir el más corto entre los listos
    auto pickShortest = [](std::vector<Process*>& ready) -> Process* {
        return *std::min_element(ready.begin(), ready.end(),
                                 [](Process* a, Process* b) {
                                     if (a->burstTime == b->burstTime)
                                         return a->arrivalTime < b->arrivalTime; // desempate estable
                                     return a->burstTime < b->burstTime;
                                 });
    };

    // Punteros para ready
    std::vector<Process*> ready;

    // Índice para descubrir procesos por llegada
    int idx = 0;

    qDebug() << "---- Ejecutando SJF (no expropiativo) ----";

    while (done < n) {
        // Ingresar a ready todos los que ya llegaron
        while (idx < n && procs[idx].arrivalTime <= currentTime) {
            if (procs[idx].state == ProcState::NEW) {
                procs[idx].state = ProcState::READY;
                ready.push_back(&procs[idx]);
            }
            idx++;
        }

        if (ready.empty()) {
            // No hay listos: saltar al próximo arrival
            if (idx < n) {
                currentTime = std::max(currentTime, procs[idx].arrivalTime);
                continue;
            }
        } else {
            // Elegir el más corto y ejecutarlo de corrido
            Process* p = pickShortest(ready);
            p->state = ProcState::RUNNING;

            p->startTime      = currentTime;
            p->finishTime     = p->startTime + p->burstTime;
            p->waitingTime    = p->startTime - p->arrivalTime;
            p->turnaroundTime = p->finishTime - p->arrivalTime;
            p->responseTime   = p->startTime - p->arrivalTime;

            qDebug() << "t=" << currentTime
                     << "-> PID:" << p->pid
                     << "(burst" << p->burstTime << ")";

            currentTime = p->finishTime;
            p->state = ProcState::TERMINATED;

            // Sacar de ready
            ready.erase(std::remove(ready.begin(), ready.end(), p), ready.end());

            done++;
        }
    }

    qDebug() << "---- Finalizado SJF ----";
    return procs;
}
