#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char* file_read(FILE* file, size_t* size);
void read(char* string, size_t size);

int main() {
FILE* file = fopen ("tree.txt", "r");
size_t* size = (size_t*)calloc(1, sizeof(size_t));
char* string = file_read(file, size);
printf("%s\n", string);
read(string, *size);
return 0;

}

char* file_read(FILE* file, size_t* size) {
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    printf("%lu\n", *size);
    char* string = (char*)calloc(*size, sizeof(char));
    rewind(file);
    fread(string, sizeof(char), *size, file);
    return string;
}

void read(char* string, size_t size) {
    size_t num = strcspn(string, "?");
    size_t newsize = size - num - 1;
    char* question = (char*)calloc(num + 1, sizeof(char));
    char* newstring = (char*)calloc(newsize, sizeof(char));

    strncpy(question, string, num + 1);
    char* begin = strchr(string, '?') + 1;
    strcpy(newstring, begin);

    free(string);
    printf("%s", newstring);
}

//     add_left(question);
//
//
// }
