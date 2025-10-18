#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSemaphore>
#include <vector>
#include <QRandomGenerator>

// ===================================================================
//      ESTE ES EL INCLUDE QUE FALTA
// ===================================================================


#include "scheduler/FCFS.h"
#include "scheduler/SJF.h"
#include "scheduler/SRTF.h"
#include "scheduler/RR.h"
#include "scheduler/PRIORITY.h"
#include "concurrency/ProducerConsumer.h"

// ... el resto de tu código sigue exactamente igual ...
// ============================================================
//   Funciones auxiliares (solo visibles en este archivo)
// ============================================================
namespace {

void imprimirPromedios(const char* nombre, const std::vector<Process>& v) {
    if (v.empty()) {
        qDebug() << "Promedios" << nombre << "-> (sin procesos)";
        return;
    }

    double sumWT = 0.0, sumTAT = 0.0, sumRT = 0.0;
    for (const auto& p : v) {
        sumWT  += p.waitingTime;
        sumTAT += p.turnaroundTime;
        sumRT  += p.responseTime;
    }

    const double n = static_cast<double>(v.size());
    qDebug() << "Promedios" << nombre
             << "-> WT:"  << (sumWT  / n)
             << "| TAT:" << (sumTAT / n)
             << "| RT:"  << (sumRT  / n);
}

void exportarResultados(const char* nombre, const std::vector<Process>& v, QTextStream& out) {
    out << "\n===== " << nombre << " =====\n";
    out << "PID\tInicio\tFin\tWT\tTAT\tRT\tEstado\n";

    for (const auto& p : v) {
        out << p.pid << "\t"
            << p.startTime << "\t"
            << p.finishTime << "\t"
            << p.waitingTime << "\t"
            << p.turnaroundTime << "\t"
            << p.responseTime << "\t"
            << (p.state == ProcState::TERMINATED ? "Terminado" : "Activo") << "\n";
    }

    double sumWT = 0, sumTAT = 0, sumRT = 0;
    for (const auto &p : v) {
        sumWT  += p.waitingTime;
        sumTAT += p.turnaroundTime;
        sumRT  += p.responseTime;
    }

    const double n = static_cast<double>(v.size());
    out << "Promedios -> WT:" << (sumWT/n)
        << " | TAT:" << (sumTAT/n)
        << " | RT:" << (sumRT/n) << "\n";
}

} // namespace


// ============================================================
//  FUNCIÓN PRINCIPAL
// ============================================================
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "==============================";
    qDebug() << "    SIMULADOR DE PLANIFICACIÓN ";
    qDebug() << "==============================";

    // Archivo de resultados
    QFile file("resultados_planificador.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "❌ No se pudo crear el archivo de resultados";
        return -1;
    }

    QTextStream out(&file);
    out << "==============================\n";
    out << "   SIMULADOR DE PLANIFICACIÓN\n";
    out << "==============================\n";

    // ----- FCFS -----
    qDebug() << "\n===== FCFS =====";
    FCFS fcfs;
    fcfs.addProcess(Process(1, 0, 5, 2));
    fcfs.addProcess(Process(2, 2, 3, 1));
    fcfs.addProcess(Process(3, 4, 1, 3));
    auto rFCFS = fcfs.run();
    imprimirPromedios("FCFS", rFCFS);
    exportarResultados("FCFS", rFCFS, out);

    // ----- SJF -----
    qDebug() << "\n===== SJF =====";
    SJF sjf;
    sjf.addProcess(Process(1, 0, 5, 2));
    sjf.addProcess(Process(2, 2, 3, 1));
    sjf.addProcess(Process(3, 4, 1, 3));
    auto rSJF = sjf.run();
    imprimirPromedios("SJF", rSJF);
    exportarResultados("SJF", rSJF, out);

    // ----- SRTF -----
    qDebug() << "\n===== SRTF =====";
    SRTF srtf;
    srtf.addProcess(Process(1, 0, 7, 2));
    srtf.addProcess(Process(2, 2, 4, 1));
    srtf.addProcess(Process(3, 4, 1, 3));
    auto rSRTF = srtf.run();
    imprimirPromedios("SRTF", rSRTF);
    exportarResultados("SRTF", rSRTF, out);

    // ----- RR -----
    qDebug() << "\n===== ROUND ROBIN =====";
    RR rr(2); // quantum = 2
    rr.addProcess(Process(1, 0, 5, 2));
    rr.addProcess(Process(2, 1, 3, 1));
    rr.addProcess(Process(3, 2, 1, 3));
    auto rRR = rr.run();
    imprimirPromedios("RR", rRR);
    exportarResultados("ROUND ROBIN", rRR, out);

    // ----- PRIORIDAD -----
    qDebug() << "\n===== PRIORIDADES =====";
    PRIORITY prio;
    prio.addProcess(Process(1, 0, 4, 3));
    prio.addProcess(Process(2, 1, 3, 1));
    prio.addProcess(Process(3, 2, 2, 2));
    auto rPR = prio.run();
    imprimirPromedios("PRIORIDAD", rPR);
    exportarResultados("PRIORIDADES", rPR, out);

    // ===== PRODUCTOR - CONSUMIDOR =====
    /*qDebug() << "\n===== PRODUCTOR - CONSUMIDOR =====";
    Buffer buffer(5);
    QSemaphore empty(buffer.maxSize);
    QSemaphore full(0);

    Producer p1(1, &buffer, &empty, &full);
    Producer p2(2, &buffer, &empty, &full);
    Consumer c1(1, &buffer, &empty, &full);
    Consumer c2(2, &buffer, &empty, &full);

    p1.start(); p2.start(); c1.start(); c2.start();
    p1.wait();  p2.wait();  c1.wait();  c2.wait();*/

    qDebug() << "=== Simulación Productor–Consumidor finalizada ===";

    // Cerrar archivo
    out << "\n==============================\n";
    out << "   SIMULACIÓN FINALIZADA OK\n";
    out << "==============================\n";
    file.close();

    qDebug() << "\n📁 Resultados exportados a 'resultados_planificador.txt'";
    qDebug() << "==============================";
    qDebug() << "   SIMULACIÓN FINALIZADA OK    ";
    qDebug() << "==============================";

    return 0;
}
