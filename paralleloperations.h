#ifndef PARALLELOPERATIONS_H
#define PARALLELOPERATIONS_H
#include <QVector>
#include <QPair>
#include <QFuture>
#include <QtConcurrent>
#include <QRandomGenerator>

//My Variant is 1, but i did already sum so i would do #3
//Parallel max and min

class parallelOperations{
public:
    parallelOperations();
    QString maxMin(qint16 threads);
private:
    QVector<qint64> array;
    qint32 arraySize;
    QVector<QFuture<QPair<qint32, qint32>>> threads;
    //pair stores IDS!!! first = max, second = min!! IDS!!!!!!!!
    QVector<QPair<qint32, qint32>> maxmins;
    QPair<qint32, qint32> parallelMaxMin(qint32 start, qint32 stop);
    QPair<qint32, qint32> checkPairs();
};

#endif // PARALLELOPERATIONS_H
