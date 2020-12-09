#include "paralleloperations.h"

parallelOperations::parallelOperations(){
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    arraySize = 9000000;
    array.resize(arraySize);
    generator.generate(array.begin(), array.end());
}

QString parallelOperations::maxMin(qint16 thrNum){

    threads.resize(thrNum);
    for(int i = 0; i < thrNum; i++){
        //threads[i] = QtConcurrent::run(this, &parallelOperations::parallelMaxMin, arraySize/thrNum*i, arraySize/thrNum*(i+1));
        threads[i] = QtConcurrent::run([&]{return this->parallelMaxMin(arraySize/thrNum*i, arraySize/thrNum*(i+1));});
    }
    for(auto i: threads){
        i.waitForFinished();
    }
    QPair<qint32, qint32> result = checkPairs();
    return "Maximum: "+QString::number(array.at(result.first))+"\tits id: "+QString::number(result.first)+"\n"
           "Minimum: "+QString::number(array.at(result.second))+"\tits id: "+QString::number(result.second);
}

QPair<qint32, qint32> parallelOperations::parallelMaxMin(qint32 start, qint32 stop){
    qint64 min,max;
    QPair<qint32, qint32> ids;
    min = array.at(start);
    max = array.at(start);
    for(int i = start; i < stop; i++){
        if(array.at(i) > max){
            max = array.at(i);
            ids.first = i;
        }
        if(array.at(i) < min){
            min = array.at(i);
            ids.second = i;
        }
    }
    return ids;
}

QPair<qint32, qint32> parallelOperations::checkPairs(){
    qint32 min, max;
    max = array.at(threads.at(0).result().first);
    min = array.at(threads.at(0).result().second);
    QPair<qint32, qint32> returnable;
    for(int i = 1; i < threads.size(); i++){
        if(array.at(threads.at(i).result().first) > max){
            max = array.at(threads.at(i).result().first);
            returnable.first = threads.at(i).result().first;
        }
        if(array.at(threads.at(i).result().second) < min){
            min = array.at(threads.at(i).result().second);
            returnable.second = threads.at(i).result().second;
        }
    }
    return returnable;
}
