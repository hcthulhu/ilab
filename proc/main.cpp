#include <iostream>
#include "stack.h"
#include "comp.h"
#include <string>

int main() {

    std::string name = "prog.txt";
    Compiler test(name, "cmd_list");
    test.read();


//    std::ofstream hex_file("prog.hex", std::ios_base::out | std::ios_base::trunc);
    std::ifstream cpu_file("prog.txt", std::ios_base::in);
    if(!cpu_file.is_open()) {
        std::cout << "false" << std::endl;
    }
//    std::ifstream cmd_file("cmd_list", std::ios_base::in);
//    char buff[50];
//    //cpu_file >> buff;
//    cpu_file.getline(buff, 50);
//    std::cout << buff << std::endl;
//    std::cout << "kkk" << std::endl;
//    hex_file << "ujdyj";

    return 0;
}