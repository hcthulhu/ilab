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
    int addr;
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
public:
   // ~Compiler();
    Compiler(std::string file_name, std::string cmd_list);

    void read();
    std::string reg_str(std::string reg);
    std::string num_str(std::string num);
    char arg_type(std::string arg);
    std::string arg_str(std::string arg, char arg_type);
    void print(std::vector<MashCmd> mash_cmd);
    void find_func(std::vector<Label> *metka, std::vector<MashCmd> *mash_cmd, const std::string str_cmd);
    void find_labels(std::vector<Label> metka, std::vector<MashCmd> *mash_cmd);
};

char int_to_hex (int digit);

#endif //PROC_COMP_H
