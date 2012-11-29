#include <QtCore/QCoreApplication>
#include <QThread>
#include <QElapsedTimer>
#include <QDebug>
#include "stack.h"


const int ASIZE = 1000000;

Stack<int> S;
class StackThread : public QThread {
public:
    StackThread(int *a, int s) {A = a; size=s;}
    virtual void run();
    int *A;
    int size;
};
void StackThread::run(){
    for (int i=0; i<size; i++) S.push(A[i]);
}



void testPar(int *A, int size) {
    QElapsedTimer timer;
    timer.start();
    StackThread *T0 = new StackThread(A,size/2);
    StackThread *T1 = new StackThread(A+size/2,size/2);
    T0->start(); T1->start();
    T0->wait();  T1->wait();
    qDebug() << "Elapsed time:" << timer.elapsed() << " ms";
    qDebug() << "After " << size << " push operations, size:" << S.getSize();
}


int main(int argc, char *argv[]) {
    int A[ASIZE];
    for (int i=0; i<ASIZE; i++) A[i] = rand()%10000;
    testPar(A,ASIZE);
    return 0;
}
