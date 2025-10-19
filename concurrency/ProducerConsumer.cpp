#include "ProducerConsumer.h"
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>

ProducerConsumer::ProducerConsumer(int capacity, QObject* parent)
    : QObject(parent), cap(capacity), buf(capacity) {}

ProducerConsumer::~ProducerConsumer() { stop(); }

void ProducerConsumer::start() {
    if (running) return;
    running = true;

    // 🔹 Conectamos los hilos directamente
    connect(&prodThread, &QThread::started, [this]() { producerLoop(); });
    connect(&consThread, &QThread::started, [this]() { consumerLoop(); });

    prodThread.start();
    consThread.start();
}

void ProducerConsumer::stop() {
    if (!running) return;

    {
        QMutexLocker lock(&m);
        running = false;
        notEmpty.wakeAll();
        notFull.wakeAll();
    }

    if (prodThread.isRunning()) {
        prodThread.quit();
        prodThread.wait();
    }
    if (consThread.isRunning()) {
        consThread.quit();
        consThread.wait();
    }

    emit bufferUpdated(QVector<int>(), 0, 0, 0);
}

void ProducerConsumer::producerLoop() {
    while (running) {
        {
            QMutexLocker lock(&m);
            if (!running) break;
            while (count == cap && running) notFull.wait(&m);
            if (!running) break;

            int val = QRandomGenerator::global()->bounded(100);
            buf[tail] = val;
            tail = (tail + 1) % cap;
            count++;

            emit produced(val);
            emit bufferUpdated(buf, head, tail, count);
            notEmpty.wakeOne();
        }
        QThread::msleep(250);
    }
}

void ProducerConsumer::consumerLoop() {
    while (running) {
        int val = -1;
        {
            QMutexLocker lock(&m);
            if (!running) break;
            while (count == 0 && running) notEmpty.wait(&m);
            if (!running) break;

            val = buf[head];
            head = (head + 1) % cap;
            count--;

            emit consumed(val);
            emit bufferUpdated(buf, head, tail, count);
            notFull.wakeOne();
        }
        QThread::msleep(400);
    }
}
