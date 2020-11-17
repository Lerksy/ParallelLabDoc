#include "CPUModel.h"

CPU::CPU(){
    //defining threads amount
    threads.resize(2);
    //limit of first queue
    threadLimit = 25;
    //every thr2Exec processes from thread 1, executing 1  process from thread 2
    thr2Exec = 5;
    //limit of processes to execute
    execLimit = 1000;
    //zeroing counter of destroyed processes in thread 1
    thr1Destroed = 0;
    //zeroing counter of created processes in thread 1
    thr1Created = 0;
    //zeroing counter of maximum amount of processes in thread 2
    thr2max = 0;
    //making model runnable only once
    isExecuted = false;
    //setting limit to thread 1
    threads[0].setMyLimit(threadLimit);
}

void CPU::exec(){
    if(!isExecuted){
        QFuture<void> creator = QtConcurrent::run(this, &CPU::processCreator);
        quint32 i = 0;
        QThread::msleep(20);
        do{
            for(int j = 0; j<thr2Exec; j++){
                threads[0].runNKillFirst();
                i++;
            }
            threads[1].runNKillFirst();
            i++;
        }while(i<execLimit);
        creator.waitForFinished();
        isExecuted = true;
    }
}

void CPU::processCreator(){
    qint16 thrNum;
    for(int i = 0; i < execLimit+(thr2Exec*2); i++){
        thrNum = QRandomGenerator::global()->bounded(0, 2);
        !threads[thrNum].createProcess() && thrNum == 0 ? thr1Destroed++ :
        thrNum == 0 ? thr1Created++ :
        thrNum == 1 ?
        threads[1].getProcessAmount() > thr2max ? thr2max = threads[1].getProcessAmount(): NULL :NULL;
        QThread::msleep(QRandomGenerator::global()->bounded(5, 11));
    }
}

QString CPU::summary(){
    QString returnable;
    if(isExecuted){
        quint32 percentage = thr1Destroed*100/(thr1Created+thr1Destroed);
        returnable += "Thread 1 drop percentage is: "+QString::number(percentage)+"\n"
                      "Thread 2 maximum amount of processes is "+QString::number(thr2max);
    }else returnable = "model wasnt executed";
    return returnable;
}

CPUProcess::CPUProcess(){
    processTimer = QRandomGenerator::global()->bounded(20, 30);
}

void CPUProcess::execute(){
    QThread::msleep(processTimer);
}

CPUQueue::CPUQueue(){
    myLimit = 0;
}

void CPUQueue::setMyLimit(quint16 limit){
    myLimit = limit;
}

bool CPUQueue::createProcess(){
    if(processes.size()<myLimit || myLimit == 0){
        CPUProcess a;
        processes.push_back(a);
        return true;
    }
    else return false;
}

quint32 CPUQueue::getProcessAmount(){
    return processes.size();
}

void CPUQueue::runNKillFirst(){
    if(processes.size()>0){
        processes[0].execute();
        processes.removeFirst();
    }
}
