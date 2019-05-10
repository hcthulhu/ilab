#include <iostream>
#include <cstring>
#include <cmath>
#include "stack.h"

Stack::~Stack() {
    num = 0;
    cap = 0;
    delete[] data;
    std::cout << "Cleaned" << std::endl;
}

Stack::Stack(unsigned int size) {
    cap = size;
    num = 0;
    data = new int[cap] {};
}

void Stack::push(int input) {
    if (num + 1 >= cap) {
        increase();
    }

    data[num++] = input;
}

int Stack::pop() {
    if (num == 0) {
        std::cout << "Stack is empty." << std::endl;
        return -10;
    }
    int ret = data[num - 1];
    data[num--] = 0;

    return ret;
}

int Stack::top() {
    if (num == 0) {
        std::cout << "Stack is empty." << std::endl;
        return -10;
    }

    return data[num - 1];
}

int Stack::empty() {
    if (num == 0) {
        std::cout << "Stack is empty." << std::endl;
        return 1;
    } else {
        std::cout << "Stack isn't empty." << std::endl;
        return 0;
    }
}

unsigned int Stack::size() {
    return num;
}

void Stack::clear() {
    if (num == 0) {
        return;
    }

    for (int cnt = num - 1; cnt > 0; cnt--) {
        data[cnt] = 0;
    }
    num = 0;
}

int Stack::peek(unsigned int n) {
    if (num == 0) {
        std::cout << "Stack is empty." << std::endl;
        return -10;
    }
    if ( n + 1 > num ) {
        std::cout << "Out of range." << std::endl;
        return -10;
    }

    return data[num - n - 1];
}

void Stack::increase() {
    auto* inc = new int[cap*2] {};
    memmove(inc, data, num*sizeof(int));
    delete[] data;
    data = inc;
    cap *= 2;
}

void Stack::print() {
    std::cout << "size = " << num << " cap = " << cap << std::endl;
    for (int i = num; i > 0; i--) {
        std::cout << data[i - 1] << std::endl;
    }
}

void Stack::sqrt() {
    double ret = std::sqrt(pop());
    push((int)ret);
}

void Stack::add() {
    int a = pop();
    int b = pop();
    push(a + b);
}

void Stack::sub() {
    int a = pop();
    int b = pop();
    push(b - a);
}

void Stack::mul() {
    int a = pop();
    int b = pop();
    push(a*b);
}

void Stack::div() {
    int a = pop();
    int b = pop();
    push(b/a);
}