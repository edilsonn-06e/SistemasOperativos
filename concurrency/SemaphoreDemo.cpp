#include "SemaphoreDemo.h"
#include <QRandomGenerator>
#include <QThread>

SemaphoreDemo::SemaphoreDemo(QObject* parent)
    : QObject(parent)
{
}

SemaphoreDemo::~SemaphoreDemo()
{
    stop();
}

void SemaphoreDemo::start()
{
    if (running) return;
    running = true;
    connect(&thread, &QThread::started, this, &SemaphoreDemo::runDemo);
    this->moveToThread(&thread);
    thread.start();
}

void SemaphoreDemo::stop()
{
    if (!running) return;
    {
        QMutexLocker lock(&mutex);
        running = false;
        cond.wakeAll();
    }
    thread.quit();
    thread.wait();
    emit finished();
}

void SemaphoreDemo::runDemo()
{
    while (running)
    {
        {
            QMutexLocker lock(&mutex);
            if (!running) break;

            if (semaphoreValue == 0)
            {
                waitingCount++;
                emit statusChanged(semaphoreValue, waitingCount, true);
                cond.wait(&mutex);
                waitingCount--;
            }

            // WAIT
            semaphoreValue = 0;
            emit statusChanged(semaphoreValue, waitingCount, true);
        }

        // Simula trabajo dentro de la región crítica
        QThread::msleep(QRandomGenerator::global()->bounded(1000, 2000));

        {
            QMutexLocker lock(&mutex);
            // SIGNAL
            semaphoreValue = 1;
            emit statusChanged(semaphoreValue, waitingCount, false);
            cond.wakeOne();
        }

        // Espera un poco antes de volver a intentar entrar
        QThread::msleep(QRandomGenerator::global()->bounded(800, 1500));
    }
}
