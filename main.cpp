#include <QCoreApplication>
#include <QElapsedTimer>
#include <QVariant>
#include <iostream>
#include "parallelVectors.h"
#include "CPUModel.h"
#include "paralleloperations.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    quint64 amount;
    quint16 cores;
    QVariant temp;
    if(argc > 2){
        temp = argv[1];
        amount = temp.toULongLong();
        temp = argv[2];
        cores = temp.toUInt();
    }else{
        amount = 9000000;
        cores = 4;
    }
    parallelVectors threading(amount);
    QElapsedTimer time1, timem;
    quint64 oneThread, multiThread;
    time1.start();
    threading.summVectors(0, 0);
    oneThread = time1.nsecsElapsed();
    threading.cleanResult();
    timem.start();
    threading.summVectors(cores);
    multiThread = timem.nsecsElapsed();
    std::cout<<"Lab1:\n\n";
    std::cout<<"One thread nanoseconds: "<<oneThread<<"\n"
                "\t\tmilliseconds: "<<oneThread/1e+6<<"\n"
                "\t\tseconds: "<<oneThread/1e+9<<"\n"
              "Multi thread nanoseconds: "<<multiThread<<"\n"
              "\tmilliseconds: "<<multiThread/1e+6<<"\n"
                "\tseconds: "<<multiThread/1e+9;

    std::cout<<std::endl<<std::endl<<std::endl<<"Lab2:\n\n";
    CPU myCPU;
    myCPU.exec();
    std::cout<<myCPU.summary().toStdString();
    std::cout<<std::endl<<std::endl<<std::endl<<"Lab3:\n\n";
    parallelOperations operation;
    std::cout<<operation.maxMin(cores).toStdString();
    return a.exec();
}
