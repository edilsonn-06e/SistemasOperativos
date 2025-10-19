#ifndef CONCURRENCYVIEW_H
#define CONCURRENCYVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPlainTextEdit>
#include <QProgressBar>
#include "../concurrency/ProducerConsumer.h"
#include "../concurrency/ReadersWriters.h"
#include "../concurrency/SleepingBarber.h"
#include "../concurrency/SemaphoreDemo.h"

class ConcurrencyView : public QWidget
{
    Q_OBJECT
public:
    explicit ConcurrencyView(QWidget* parent = nullptr);

private:
    // Componentes visuales
    QTableWidget* tblBuf;
    QLabel *lblRW, *lblSB, *lblSem;
    QPlainTextEdit* txtLog;
    QProgressBar* barSem;

    // Módulos de concurrencia
    ProducerConsumer pc;
    ReadersWriters rw;
    SleepingBarber sb;
    SemaphoreDemo semDemo;
};

#endif // CONCURRENCYVIEW_H
