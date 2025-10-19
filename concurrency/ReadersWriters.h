#pragma once
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class ReadersWriters : public QObject {
    Q_OBJECT
public:
    explicit ReadersWriters(QObject* parent = nullptr);
    ~ReadersWriters();

    void start();
    void stop();

signals:
    void startedReading();
    void startedWriting();
    void finished();

private:
    void readerLoop();
    void writerLoop();

    bool running = false;
    int readers = 0;
    QMutex mutex;
    QWaitCondition canRead, canWrite;
    QThread readerThread, writerThread;
};
