#pragma once
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QVector>

class ProducerConsumer : public QObject {
    Q_OBJECT
public:
    explicit ProducerConsumer(int capacity = 8, QObject* parent = nullptr);
    ~ProducerConsumer();

    void start();
    void stop();

signals:
    void produced(int value);
    void consumed(int value);
    void bufferUpdated(QVector<int> buffer, int head, int tail, int count);

private:
    void producerLoop();
    void consumerLoop();

    bool running = false;
    int cap;
    int head = 0, tail = 0, count = 0;
    QVector<int> buf;
    QThread prodThread, consThread;
    QMutex m;
    QWaitCondition notFull, notEmpty;
};
