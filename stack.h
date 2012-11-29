#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;


//
// Template class for a sequential Stack
//

template <typename T>
class Node {
public:
    Node<T>() {}
    Node<T>(T d, Node<T> *n=NULL) { data = d; next = n; }
    void display(ostream &out) {out << data;}
    T data;
    Node<T> *next;
};

template <typename T>
class Stack {
private:
    Node<T> *top;
public:
    Stack<T>() {top = NULL;}

    void push(T value) {
        Node<T> *n = new Node<T>(value, top);
        top = n;
        return;
    }

    T pop() {
        Node<T> *n = top->next;
        T value = top->data;
        delete top;
        top = n;
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

#endif // STACK_H
