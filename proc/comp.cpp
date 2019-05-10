#include "comp.h"
#include <fstream>
#include <cstring>
#include <cstdio>

const Reg def_reg[4] = { "ax", "01",
                         "bx", "02",
                         "cx", "03",
                         "dx", "04" };

void Compiler::read() {

    if(!(cpu_file.is_open() && cmd_file.is_open())) {
        std::cout << "File opening error" << std::endl;
        exit(-1);
    }

    Command tmp_cmd = {};

    for( int i = 0 ; !cmd_file.eof() ; i++) {
        cmd_file >> tmp_cmd.cmd >> tmp_cmd.hex_cmd >> tmp_cmd.arg1 >> tmp_cmd.arg2;
        tmp_cmd.length = 3;

        if (tmp_cmd.arg1 == 'r' || tmp_cmd.arg1 == 'm')
            tmp_cmd.length += 3;
        if (tmp_cmd.arg1 == 'n')
            tmp_cmd.length += 12;
        if (tmp_cmd.arg2 == 'r' || tmp_cmd.arg2 == 'm')
            tmp_cmd.length += 3;
        if (tmp_cmd.arg2 == 'n')
            tmp_cmd.length += 12;

        cmd.push_back(tmp_cmd);
    }

    std::string str_cmd = {};

    int pointer = 0;
    std::vector<Label> metka;
    std::vector<MashCmd> mash_cmd = {};


    for ( ; !cpu_file.eof() ; ) {
        getline(cpu_file, str_cmd);
        find_func(&metka, &mash_cmd, str_cmd);
    }

    find_labels(metka, &mash_cmd);

    print(mash_cmd);

    cpu_file.seekg(0);

}

Compiler::Compiler(std::string file_name, std::string cmd_list):
    hex_file("prog.hex", std::ios_base::out | std::ios_base::trunc),
    cpu_file(file_name.data(), std::ios_base::in),
    cmd_file(cmd_list, std::ios_base::in) {}

char Compiler::arg_type(std::string arg) {
    int len = arg.length();

    if ( len == 0 )
        return 'e';

    for ( const auto num : def_reg ) {
        if ( arg == num.reg )
            return 'r';
    }

    if ( (arg.data()[0] == '<') && (arg.data()[len - 1] == '>') )
        return 'm';

    for ( int i = 0; arg.data()[i] != '\0'; i++ ) {
        if ( !std::isdigit(arg.data()[i]) ) {
            std::cout << "Wrong argument" << std::endl;
            exit(-1);
        }
    }

    return 'n';
}

std::string Compiler::arg_str(std::string arg, char arg_type) {
    switch (arg_type) {
        case 'r':
            return reg_str(arg);

        case 'n':
            return num_str(arg);

        case 'm':
            return arg;
        default:
            return "";
    }
}

std::string Compiler::reg_str(std::string reg) {
    std::string ret = {};

    for ( const auto num : def_reg ) {
        if ( reg == num.reg ) {
            ret += num.hex_reg;
        }
    }

    return ret;
}

std::string Compiler::num_str(std::string num) {
    int inum = std::stoi(num);
    int digit = 0;
    int pow = 1;
    std::string ret = {};

    for (int i = 0; i <= 7; i++) {
        for (int k = 7; k > i; k--) {
            pow *= 16;
        }
        digit = inum / pow % 16;

        ret += int_to_hex(digit);
        if (i % 2 == 1) {
            ret += " ";
        }
        pow = 1;
    }

    ret.pop_back();

    return ret;
}

char int_to_hex (int digit) {
    switch (digit) {
        case 10:
            return 'a';
        case 11:
            return 'b';
        case 12:
            return 'c';
        case 13:
            return 'd';
        case 14:
            return 'e';
        case 15:
            return 'f';
        default:
            return digit + 48;
    }
}

void Compiler::print(std::vector<MashCmd> mash_cmd) {
    for (const auto num : mash_cmd) {
        hex_file << num.hex_cmd << " ";
        if (num.arg1 != "") {
            hex_file << num.arg1 << " ";
        }
        if (num.arg2 != "") {
            hex_file << num.arg2 << " ";
        }
    }
}

void Compiler::find_func(std::vector<Label> *metka, std::vector<MashCmd> *mash_cmd, const std::string str_cmd) {
    std::string word[3] = {};
    MashCmd tmp_mcmd = {};
    Label tmp_metka = {};

    int mlen = 0;
    int ptr = 0;
    int err = -1;

    for (int i = 0, j = 0; str_cmd.data()[i] != '\0'; i++) {
        if (str_cmd.data()[i] == ' ') {
            j++;
        } else {
            word[j] += str_cmd.data()[i];
        }
    }

    mlen = word[0].length();

    for (const auto num : cmd) {
        if ((word[0] == num.cmd) &&
            (arg_type(word[1]) == num.arg1) &&
            (arg_type(word[2]) == num.arg2)) {

            tmp_mcmd.hex_cmd += num.hex_cmd;
            tmp_mcmd.arg1 += arg_str(word[1], num.arg1);
            tmp_mcmd.arg2 += arg_str(word[2], num.arg2);

            mash_cmd->push_back(tmp_mcmd);

            ptr += num.length;
            err = 0;
            break;

        } else if ( (word[0].data()[0] == '<') &&
                    (word[0].data()[mlen - 2] == '>') &&
                    (word[0].data()[mlen - 1] == ':') ) {
            tmp_metka.addr += ptr;
            tmp_metka.name += word[0];

            metka->push_back(tmp_metka);
        }
    }

    if (err == -1 && !cpu_file.eof()) {
        std::cout << "No matching function" << std::endl;
        exit(-1);
    }
}

void Compiler::find_labels(std::vector<Label> metka, std::vector<MashCmd> *mash_cmd) {
    int size = mash_cmd->size();
    for ( int i = 0; i < size; i++ ) {
        for ( const auto label : metka ) {
            if (*(mash_cmd + i)->arg1.data() == label.name) {
                *(mash_cmd + i)->arg1.clear();
                *(mash_cmd + i)->arg1 += label.name;
            }
        }
    }
}