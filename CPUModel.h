#ifndef PARALLEL2_H
#define PARALLEL2_H
#include <QVector>
#include <QRandomGenerator>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <iostream>



class CPUProcess{
public:
    CPUProcess();
    void execute();
private:
    quint32 processTimer;
};

class CPUQueue{
public:
    CPUQueue();
    void setMyLimit(quint16 limit);
    bool createProcess();
    quint32 getProcessAmount();
    void runNKillFirst();
private:
    QVector<CPUProcess> processes;
    quint16 myLimit;
};


class CPU{
public:
    CPU();
    void exec();
    void processCreator();
    QString summary();
private:
    bool isExecuted;
    QVector<CPUQueue> threads;
    quint16 threadLimit;
    quint16 thr2Exec;
    quint16 execLimit;
    quint32 thr1Destroed;
    quint32 thr1Created;
    quint32 thr2max;
};
#endif // PARALLEL2_H
