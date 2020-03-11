#ifndef PROC_CPU_H
#define PROC_CPU_H

#include "stack.h"
#include <iostream>

class CPU {
private:
    int ax, bx, cx, dx;
    Stack stack;
    int ip, sp, bp;

public:
    void halt();    // ed
    void dump();    // 88

    void Rpush();   // a1
    void Npush();   // a2

    void Rpop();    // b1
    void pop();     // b2

    void Rmov();    // d1
    void Nmov();    // d2
    void RNmov();   // d3

    void Rcmp();    // c1
    void Ncmp();    // c2
    void Scmp();    // c3

    void jmp();     // e0
    void je();      // e1
    void ja();      // e2
    void jb();      // e3
    void jne();     // e4

    void call();    // ff
    void print();   // f1
    void write();   // f2


};


void read(FILE* file);

#endif //PROC_CPP_H

