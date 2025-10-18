#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "Scheduler.h"  // Asegúrate de incluir la clase base Scheduler
#include "Scheduler.h"  // Incluir el archivo que contiene la clase Scheduler

class FCFS : public Scheduler {
public:
    std::vector<Process> processes;  // Lista de procesos

    // Método que corre la simulación FCFS
    std::vector<Process> run();  // Método para ejecutar FCFS

    // Método para agregar un proceso
    void addProcess(const Process& p) {
        processes.push_back(p);
    }
};

#endif // FCFS_H
