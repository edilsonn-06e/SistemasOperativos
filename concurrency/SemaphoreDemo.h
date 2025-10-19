#ifndef SEMAPHOREDEMO_H
#define SEMAPHOREDEMO_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SemaphoreDemo : public QObject
{
    Q_OBJECT
public:
    explicit SemaphoreDemo(QObject* parent = nullptr);
    ~SemaphoreDemo();

public slots:
    void start();
    void stop();

signals:
    void statusChanged(int value, int waiting, bool locked);
    void finished();

private:
    void runDemo();
    bool running = false;

    int semaphoreValue = 1; // Valor inicial del semáforo (1 = libre)
    int waitingCount = 0;
    QMutex mutex;
    QWaitCondition cond;
    QThread thread;
};

#endif // SEMAPHOREDEMO_H
