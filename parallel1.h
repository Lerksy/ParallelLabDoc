#ifndef PARALLEL1_H
#define PARALLEL1_H
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QtMath>

class parallel1{
public:
    parallel1();
    parallel1(quint64 size);
    void summVectors(quint64 start, quint64 stop);
    void summVectors(quint16 threads);
    void printResult();
    void cleanResult();
private:
    quint64 defaultSize;
    QVector<qint64> first;
    QVector<qint64> second;
    QVector<qint64> result;

};

#endif // PARALLEL1_H
