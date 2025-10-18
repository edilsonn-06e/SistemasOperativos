#include "FCFS.h"
#include <algorithm>
#include <QDebug>

std::vector<Process> FCFS::run() {
    // Ordenar los procesos por tiempo de llegada
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    for (auto& p : processes) {
        // Si la CPU está inactiva, avanzar el tiempo hasta la llegada del proceso
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }

        // Calcular métricas
        p.startTime = currentTime;
        p.responseTime = p.startTime - p.arrivalTime;
        p.waitingTime = p.responseTime;
        p.finishTime = p.startTime + p.burstTime;
        p.turnaroundTime = p.finishTime - p.arrivalTime;
        p.state = ProcState::TERMINATED;  // Asegúrate de que ProcState esté definido correctamente

        // El tiempo actual avanza al final de la ejecución de este proceso
        currentTime = p.finishTime;
    }

    // Mostrar los resultados después de la simulación
    qDebug() << "FCFS: Simulación completada.";
    qDebug() << "PID\tTiempo de llegada\tTiempo de ejecución\tTiempo de espera\tTiempo de respuesta\tTiempo de turnaround";
    for (const auto& p : processes) {
        qDebug() << p.pid << "\t" << p.arrivalTime << "\t\t" << p.burstTime
                 << "\t\t" << p.waitingTime << "\t\t" << p.responseTime << "\t\t" << p.turnaroundTime;
    }

    return processes;
}
