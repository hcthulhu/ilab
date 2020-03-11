#ifndef PROC_STACK_H
#define PROC_STACK_H

#include <cstring>
#include <iostream>

class Stack {
private:
    unsigned int num;
    unsigned int cap;
    int* data;

public:
    ~Stack();
    explicit Stack(unsigned int size = 30);

    void push(int);
    int pop();
    int top();
    int empty();
    unsigned int size();
    void clear();
    int peek(unsigned int);
    void increase();
    void print();

    //arithmetic
    void sqrt();
    void add();
    void sub();
    void mul();
    void div();
};

#endif //PROC_STACK_H
