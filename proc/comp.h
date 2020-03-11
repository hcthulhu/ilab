#ifndef PROC_COMP_H
#define PROC_COMP_H

#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

struct Command {
    std::string cmd;
    std::string hex_cmd;
    char arg1;
    char arg2;
    int length;
};

struct MashCmd {
    std::string hex_cmd;
    std::string arg1;
    std::string arg2;
};

struct Label {
    std::string name;
    std::string addr;
};

struct Reg {
    std::string reg;
    std::string hex_reg;
};

class Compiler {
private:
    std::ifstream cpu_file;
    std::ofstream hex_file;
    std::ifstream cmd_file;

    std::vector<Command> cmd;
    std::vector<MashCmd> mach_cmd;
    std::vector<Label> metka;
    int ptr;
    int line_ptr;
    int err;
    int err_flag;
public:
    Compiler(std::string file_name, std::string cmd_list);

    void read();
    std::string reg_str(std::string reg);
    std::string num_str(std::string num);
    std::string lbl_str(std::string addr);
    char arg_type(std::string arg);
    std::string arg_str(std::string arg, char arg_type);
    void print();
    void find_func(const std::string str_cmd);
    void find_labels();
    void read_cmd(const std::string str_cmd, std::string &name, std::string &arg1, std::string &arg2);

};

char int_to_hex (int digit);
void SPskip(int &i, std::string string);

#endif //PROC_COMP_H

