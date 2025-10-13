#pragma once
#include "../core/Process.h"
#include <vector>

class Scheduler {
public:
    virtual void addProcess(const Process &p) = 0;      // Agregar proceso
    virtual std::vector<Process> run() = 0;             // Ejecutar planificación
    virtual ~Scheduler() = default;                     // Destructor virtual
};
