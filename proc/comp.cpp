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
        err = 10;
        exit(err);
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

    for ( ; !cpu_file.eof() ; ) {
        line_ptr++;
        getline(cpu_file, str_cmd);
        find_func(str_cmd);
    }

    find_labels();

    print();

    cpu_file.close();
    cmd_file.close();
    hex_file.close();

    if (err_flag) {
        exit(5);
    }

}

Compiler::Compiler(std::string file_name, std::string cmd_list):
    hex_file("prog.hex", std::ios_base::out | std::ios_base::trunc),
    cpu_file(file_name, std::ios_base::in),
    cmd_file(cmd_list, std::ios_base::in) {
    ptr = 0;
    line_ptr = 0;
    err = 0;
    err_flag = 0;
}

char Compiler::arg_type(std::string arg) {
    int len = arg.length();

    if ( len == 0 )
        return 'e';

    for ( const auto num : def_reg ) {
        if ( arg == num.reg )
            return 'r';
    }

    if ( arg[0] == '_' )
        return 'm';

    for ( int i = 0; arg[i] != '\0'; i++ ) {
        if ( !std::isdigit(arg[i]) ) {
            return -1;
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

std::string Compiler::lbl_str(std::string addr) {
    int i_addr = std::stoi(addr);
    std::string ret = {};

    ret += int_to_hex(i_addr / 16 % 16);
    ret += int_to_hex(i_addr % 16);

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

void Compiler::print() {
    for (const auto num : mach_cmd) {
        hex_file << num.hex_cmd << " ";
        if (num.arg1 != "") {
            hex_file << num.arg1 << " ";
        }
        if (num.arg2 != "") {
            hex_file << num.arg2 << " ";
        }
    }
}

void SPskip(int &i, std::string string) {
    while ( string[i] == ' ' ) {
        i++;
    }
    if ( string[i] == '/' ) {
        i++;
        while ( string[i] != '/' && string[i] != '\0') {
            i++;
        }
        i++;
    }
    while ( string[i] == ' ' ) {
        i++;
    }
}

void Compiler::read_cmd(const std::string str_cmd, std::string &name, std::string &arg1, std::string &arg2) {
    int i = 0;
    SPskip(i, str_cmd);
    for ( ; str_cmd[i] != ' ' && str_cmd[i] != '\0' && str_cmd[i] != '/' ; i++) {
        name += str_cmd[i];
    }
    SPskip(i, str_cmd);
    for ( ; str_cmd[i] != ' ' && str_cmd[i] != '\0' && str_cmd[i] != '/' ; i++) {
        arg1 += str_cmd[i];
    }
    SPskip(i, str_cmd);
    for ( ; str_cmd[i] != ' ' && str_cmd[i] != '\0' && str_cmd[i] != '/' ; i++) {
        arg2 += str_cmd[i];
    }
    SPskip(i, str_cmd);
    if ( str_cmd[i] == '/' || str_cmd[i] == '\0') {
        return;
    } else {
        err = 15;
        err_flag = 1;
        std::cout << "Too many arguments in line " << line_ptr << std::endl;
    }
}

void Compiler::find_func(const std::string str_cmd) {

    std::string name = {};
    std::string arg1 = {};
    std::string arg2 = {};

    MashCmd tmp_mcmd = {};
    Label tmp_metka = {};
    std::string sptr = {};

    int mlen = 0;

    read_cmd(str_cmd, name, arg1, arg2);
    mlen = name.length();

    for (const auto num : cmd) {
        err = 1;
        if ((arg_type(arg1) == -1) || (arg_type(arg2) == -1)) {
            err = 5;
            err_flag = 1;
            std::cout << "Wrong argument in line " << line_ptr << std::endl;
            break;
        }
        if ((name == num.cmd) &&
            (arg_type(arg1) == num.arg1) &&
            (arg_type(arg2) == num.arg2)) {

            tmp_mcmd.hex_cmd += num.hex_cmd;
            tmp_mcmd.arg1 += arg_str(arg1, num.arg1);
            tmp_mcmd.arg2 += arg_str(arg2, num.arg2);

            mach_cmd.push_back(tmp_mcmd);

            ptr += num.length;
            err = 0;
            break;

        } else if ( (name[0] == '_') &&
                    (name[mlen - 1] == ':') ) {
            sptr += lbl_str(std::to_string(ptr));
            tmp_metka.addr += sptr;
            name.pop_back();
            tmp_metka.name += name;

            metka.push_back(tmp_metka);

            err = 0;
            break;
        }
    }

    if ( (err == 1) && !cpu_file.eof()) {
        err_flag = 1;
        std::cout << "No matching function in line " << line_ptr << std::endl;
    }
}

void Compiler::find_labels() {
    int size = mach_cmd.size();
    for ( int i = 0; i < size; i++ ) {
        if (mach_cmd[i].arg1[0] == '_') {
            err = 20;
            for ( const auto label : metka ) {
                if (mach_cmd[i].arg1 == label.name) {
                    mach_cmd[i].arg1.clear();
                    mach_cmd[i].arg1 += label.addr;
                    err = 0;
                    break;
                }
            }
            if (err) {
                err_flag = 1;
                std::cout << "Metka " << mach_cmd[i].arg1 << " doesn't exist" << std::endl;
            }
        }
    }
}

