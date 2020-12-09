#include "parallelVectors.h"

parallelVectors::parallelVectors(){
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    defaultSize = 12;
    first.resize(defaultSize);
    second.resize(defaultSize);
    result.resize(defaultSize);
    generator.generate(first.begin(), first.end());
    generator.generate(second.begin(), second.end());
}

parallelVectors::parallelVectors(quint64 size)
{
    defaultSize = size;
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    first.resize(defaultSize);
    second.resize(defaultSize);
    result.resize(defaultSize);
    generator.generate(first.begin(), first.end());
    generator.generate(second.begin(), second.end());
}

void parallelVectors::summVectors(quint64 start, quint64 stop){
    if(stop == 0 || stop > defaultSize) stop = defaultSize;
       for(quint32 i = start; i < stop; i++){
            result[i] = first.at(i)+second.at(i);
       }
}

void parallelVectors::summVectors(quint16 threads){
    QVector<QFuture<void>> sumThreads;
    sumThreads.resize(threads);
    for(int i = 0; i < threads; i++){
        //sumThreads[i] = QtConcurrent::run(&parallelVectors::summVectors, this, static_cast<quint64>(defaultSize/threads*i), defaultSize/threads*(i+1));
        sumThreads[i] = QtConcurrent::run([&]{this->summVectors(defaultSize/threads*i, defaultSize/threads*(i+1));});
    }
    for(auto i:sumThreads){
        i.waitForFinished();
    }
}

void parallelVectors::printResult()
{
    qDebug()<<result;
}

void parallelVectors::cleanResult()
{
    result.clear();
    result.resize(defaultSize);
}
