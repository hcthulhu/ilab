#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

class Tree {
private:
    char *cell;
    Tree *left;
    Tree *right;

public:
    Tree ();
    void read(char* string, size_t size) {
        size_t num = strcspn(string, "?");
        size_t newsize = size - num - 1;
        char* question = (char*)calloc(num + 1, sizeof(char));
        char* newstring = (char*)calloc(newsize, sizeof(char));

        strncpy(question, string, num + 1);
        char* begin = strchr(string, '?') + 1;
        strcpy(newstring, begin);

        free(string);

        add_left(question);
        left->read(newstring, newsize);

    }

    void write(FILE* file);
    void full_print();
    void add_left(char* data);
    void add_right(char* data);
    void print();
    char* get();
    void add_data(char* data);
    ~Tree();
};

Tree::Tree () {
    cell = NULL;
    left = NULL;
    right = NULL;
}

Tree::~Tree () {
    delete cell;
}
