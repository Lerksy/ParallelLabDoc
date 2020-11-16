#include <QCoreApplication>
#include <QElapsedTimer>
#include <QVariant>
#include <iostream>
#include "parallel1.h"
#include "parallel2.h"

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
    parallel1 threading(amount);
    QElapsedTimer time1, timem;
    quint64 oneThread, multiThread;
    time1.start();
    threading.summVectors(0, 0);
    oneThread = time1.nsecsElapsed();
    threading.cleanResult();
    timem.start();
    threading.summVectors(cores);
    multiThread = timem.nsecsElapsed();
    std::cout<<"One thread nanoseconds: "<<oneThread<<"\n"
                "\t\tmilliseconds: "<<oneThread/1e+6<<"\n"
                "\t\tseconds: "<<oneThread/1e+9<<"\n"
              "Multi thread nanoseconds: "<<multiThread<<"\n"
              "\tmilliseconds: "<<multiThread/1e+6<<"\n"
                "\tseconds: "<<multiThread/1e+9;

    std::cout<<std::endl<<std::endl<<std::endl<<"Lab2:\n";
    CPU myCPU;
    myCPU.exec();
    std::cout<<myCPU.summary().toStdString();
    return a.exec();
}
