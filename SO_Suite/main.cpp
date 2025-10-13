#include <QApplication>
#include <QDebug>
#include "scheduler/SRTF.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SRTF scheduler;

    scheduler.addProcess(Process(1, 0, 7, 2));
    scheduler.addProcess(Process(2, 2, 4, 1));
    scheduler.addProcess(Process(3, 4, 1, 3));

    auto result = scheduler.run();

    qDebug() << "----- RESULTADO FINAL -----";
    for (auto &p : result) {
        qDebug() << "PID:" << p.pid
                 << "Estado:"
                 << (p.state == ProcState::TERMINATED ? "Terminado" : "Activo");
    }

    return 0;
}
