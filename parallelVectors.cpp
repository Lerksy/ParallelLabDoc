#include "parallelVectors.h"

parallel1::parallel1(){
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    defaultSize = 12;
    first.resize(defaultSize);
    second.resize(defaultSize);
    result.resize(defaultSize);
    generator.generate(first.begin(), first.end());
    generator.generate(second.begin(), second.end());
}

parallel1::parallel1(quint64 size)
{
    defaultSize = size;
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    first.resize(defaultSize);
    second.resize(defaultSize);
    result.resize(defaultSize);
    generator.generate(first.begin(), first.end());
    generator.generate(second.begin(), second.end());
}

void parallel1::summVectors(quint64 start, quint64 stop){
    if(stop == 0 || stop > defaultSize) stop = defaultSize;
       for(quint32 i = start; i < stop; i++){
            result[i] = first.at(i)+second.at(i);
       }
}

void parallel1::summVectors(quint16 threads)
{
    QVector<QFuture<void>> sumThreads;
    sumThreads.resize(threads);
    for(int i = 0; i < threads; i++){
        sumThreads[i] = QtConcurrent::run(this, &parallel1::summVectors, defaultSize/threads*i,defaultSize/threads*(i+1));
    }
    for(auto i:sumThreads){
        i.waitForFinished();
    }
}

void parallel1::printResult()
{
    qDebug()<<result;
}

void parallel1::cleanResult()
{
    result.clear();
    result.resize(defaultSize);
}
