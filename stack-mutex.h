#ifndef STACKMUTEX_H
#define STACKMUTEX_H

#include <iostream>
#include <QMutex>

using namespace std;

#include "stack.h"

template <typename T>
class StackMutex {
private:
    Node<T> *top;
    QMutex mutex;

public:
    StackMutex<T>() {top = NULL;};
    void push(T value) {

        Node<T> *n = new Node<T>(value);

        // Atomize the critical region
        mutex.lock();
        n->next = top;
        top = n;
        mutex.unlock();

        return;
    }
    T pop() {

        Node<T> *n = top->next;
        mutex.lock();
        T value = top->data;
        top = n;
        mutex.unlock();
        delete top;
        return(value);
    }
    T getTop() { return top->data; }
    void display(ostream &out) {
        Node <T> *c = top;
        while(c!=NULL) {
            out << c->data << " ";
            c = c->next;
        }
        out << endl;
    }
    int getSize() {
        int n = 0;
        Node <T> *c = top;
        while(c!=NULL) {
            c = c->next;
            n++;
        }
        return n;
    }
};


#endif // STACKMUTEX_H
