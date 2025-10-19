#include "ReadersWriters.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>

ReadersWriters::ReadersWriters(QObject* parent)
    : QObject(parent) {}

ReadersWriters::~ReadersWriters() { stop(); }

void ReadersWriters::start() {
    if (running) return;
    running = true;

    connect(&readerThread, &QThread::started, [this]() { readerLoop(); });
    connect(&writerThread, &QThread::started, [this]() { writerLoop(); });

    readerThread.start();
    writerThread.start();
}

void ReadersWriters::stop() {
    if (!running) return;
    {
        QMutexLocker lock(&mutex);
        running = false;
        canRead.wakeAll();
        canWrite.wakeAll();
    }

    if (readerThread.isRunning()) {
        readerThread.quit();
        readerThread.wait();
    }
    if (writerThread.isRunning()) {
        writerThread.quit();
        writerThread.wait();
    }

    emit finished();
}

void ReadersWriters::readerLoop() {
    while (running) {
        {
            QMutexLocker lock(&mutex);
            if (!running) break;
            while (readers < 0 && running) canRead.wait(&mutex);
            if (!running) break;
            readers++;
            emit startedReading();
        }

        QThread::msleep(QRandomGenerator::global()->bounded(400, 1000));
        if (!running) break;

        {
            QMutexLocker lock(&mutex);
            readers--;
            if (readers == 0) canWrite.wakeOne();
            emit finished();
        }

        QThread::msleep(QRandomGenerator::global()->bounded(600, 1200));
    }
}

void ReadersWriters::writerLoop() {
    while (running) {
        {
            QMutexLocker lock(&mutex);
            if (!running) break;
            while (readers != 0 && running) canWrite.wait(&mutex);
            if (!running) break;
            readers = -1;
            emit startedWriting();
        }

        QThread::msleep(QRandomGenerator::global()->bounded(700, 1500));
        if (!running) break;

        {
            QMutexLocker lock(&mutex);
            readers = 0;
            canRead.wakeAll();
            emit finished();
        }

        QThread::msleep(QRandomGenerator::global()->bounded(1000, 2000));
    }
}
