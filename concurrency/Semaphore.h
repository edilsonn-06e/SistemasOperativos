
#pragma once
#include <QSemaphore>

// Simple wrapper for clarity / future extension
class Semaphore {
public:
    QSemaphore sem;
    explicit Semaphore(int initial=0): sem(initial) {}
    void acquire(int n=1){ sem.acquire(n); }
    void release(int n=1){ sem.release(n); }
    int available() const { return sem.available(); }
};
