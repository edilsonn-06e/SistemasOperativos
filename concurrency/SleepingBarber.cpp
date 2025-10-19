#include "SleepingBarber.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>

SleepingBarber::SleepingBarber(int chairs, QObject* parent)
    : QObject(parent), chairs(chairs) {}

SleepingBarber::~SleepingBarber() { stop(); }

void SleepingBarber::start() {
    if (running) return;
    running = true;

    connect(&barberThread, &QThread::started, [this]() { barberLoop(); });
    connect(&customerThread, &QThread::started, [this]() { customerLoop(); });

    barberThread.start();
    customerThread.start();
}

void SleepingBarber::stop() {
    if (!running) return;
    {
        QMutexLocker lock(&mutex);
        running = false;
        barberWake.wakeAll();
    }

    if (barberThread.isRunning()) {
        barberThread.quit();
        barberThread.wait();
    }
    if (customerThread.isRunning()) {
        customerThread.quit();
        customerThread.wait();
    }

    emit finished();
}

void SleepingBarber::barberLoop() {
    while (running) {
        {
            QMutexLocker lock(&mutex);
            if (!running) break;
            if (waiting == 0) {
                emit sleeping();
                barberWake.wait(&mutex);
                if (!running) break;
            }

            waiting--;
            emit startedCutting();
        }

        QThread::msleep(QRandomGenerator::global()->bounded(1000, 2000));
        if (!running) break;
        emit finished();
    }
}

void SleepingBarber::customerLoop() {
    while (running) {
        QThread::msleep(QRandomGenerator::global()->bounded(800, 1800));
        if (!running) break;

        QMutexLocker lock(&mutex);
        if (!running) break;

        if (waiting < chairs) {
            waiting++;
            barberWake.wakeOne();
        }
    }
}
