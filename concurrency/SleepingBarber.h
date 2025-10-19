#pragma once
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SleepingBarber : public QObject {
    Q_OBJECT
public:
    explicit SleepingBarber(int chairs = 3, QObject* parent = nullptr);
    ~SleepingBarber();

    void start();
    void stop();

signals:
    void sleeping();
    void startedCutting();
    void finished();

private:
    void barberLoop();
    void customerLoop();

    bool running = false;
    int chairs;
    int waiting = 0;
    QMutex mutex;
    QWaitCondition barberWake;
    QThread barberThread, customerThread;
};
