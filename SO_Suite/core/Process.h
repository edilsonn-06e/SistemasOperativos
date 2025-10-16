#pragma once
#include <QString>

// Posibles estados del proceso
enum class ProcState { NEW, READY, RUNNING, WAITING, TERMINATED };

// Estructura base de un proceso
struct Process {
    int pid;            // ID del proceso
    int arrivalTime;    // Tiempo de llegada
    int burstTime;      // Duración total
    int priority;       // Nivel de prioridad (menor = más prioridad)
    int remainingTime;  // Tiempo restante
    ProcState state;    // Estado actual

    // --- MÉTRICAS ---
    int startTime = -1;       // Primer instante en que corre
    int finishTime = 0;       // Instante en que termina
    int waitingTime = 0;      // WT = finish - arrival - burst
    int turnaroundTime = 0;   // TAT = finish - arrival
    int responseTime = 0;     // RT = start - arrival

    // Constructor
    Process(int id, int arrival, int burst, int prio)
        : pid(id), arrivalTime(arrival), burstTime(burst),
        priority(prio), remainingTime(burst), state(ProcState::NEW) {}
};

