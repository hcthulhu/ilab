#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main () {
    FILE* phones = fopen("phones.txt", "w");
    srand(time(NULL));
    long long int num = 0;
    char* name = (char*)calloc(21, sizeof(char));

    for (int cntr = 0; cntr < 10000; cntr++) {
        num = 79000000000 + rand()%1000000000;
        int i = 1, j = 1;
        name[0] = (char)(rand()%26 + 65);
        for ( ; i <= 4 + rand()%5; i++) {
            name[i] = (char)(rand()%26 + 97);
        }
        name[i] = ' ';
        name[i+1] = (char)(rand()%26 + 65);
        for ( ; j <= 6 + rand()%4; j++) {
            name[i+1+j] = (char)(rand()%26 + 97);
        }
        name[i+1+j] = '\0';
        fprintf (phones, "%lld %s\n", num, name);
        bzero (name, 21);
    }

    return 0;
}
