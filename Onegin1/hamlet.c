#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <stdlib.h>

const int MaxStr = 10000;

struct _string {
    char* smb;
    int length;
};
typedef struct _string string;

int ReadData(string** poem, char** SolidTXT, int* SmbAmt, int* StrAmt);
void WriteToFile(string* poem, int StrAmt);

int main() {
    string* poem = NULL;
    char* SolidTXT = NULL;
    int SmbAmt = 0;
    int StrAmt = 0;
    //poem = (string*)calloc(MaxStr, sizeof(string));
    ReadData(&poem, &SolidTXT, &SmbAmt, &StrAmt);

    printf ("%c", *poem->smb);
    // SortData1();
    // SortData2();
    // WriteToFile(poem, StrAmt);
    // free(poem);
    // free(SolidTXT);
}

int ReadData(string** poem, char** SolidTXT, int* SmbAmt, int* StrAmt) {
    FILE* hamlet = fopen ("hamlet.txt", "r");
    if (!hamlet) {printf ("Can't open hamlet.txt\n"); return -1;}

    struct stat st = {};
    stat ("hamlet.txt", &st);
    *SmbAmt = (int)st.st_size;

    *SolidTXT = (char*)calloc(*SmbAmt, sizeof(char));
    fread(*SolidTXT, sizeof(char), *SmbAmt, hamlet);

    *poem = (string*)calloc(MaxStr, sizeof(string));
    *poem[0]->smb = **SolidTXT;

    int Nstr = 0;
    for (int cntr = 0, str_lengh = 0; cntr <= *SmbAmt; cntr++) {
        str_lengh++;
        if ((*SolidTXT[cntr] == '\n') || (*SolidTXT[cntr] == EOF)) {
            *poem[Nstr + 1]->smb = *SolidTXT[cntr + 1];
            poem[Nstr]->length = str_lengh;
            str_lengh = 0;
            Nstr++;
        }
    }
    *StrAmt = Nstr;
    *poem = (string*)realloc(poem, (Nstr)*sizeof(string));

    for (int Nstr = 0; Nstr <= *StrAmt; Nstr++) {
        for (int Nsmb = 0; Nsmb <= poem[Nstr]->length - 1; Nsmb++) {
            printf("%c", *(poem[Nstr]->smb + Nsmb));
        }
    }

    fclose (hamlet);



    for (int i = 0; i <= *SmbAmt; i++) {
        printf("%c", *SolidTXT[i]);
    }
    return 1;
}

void WriteToFile(string* poem, int StrAmt) {
    for (int Nstr = 0; Nstr <= StrAmt; Nstr++) {
        for (int Nsmb = 0; Nsmb <= poem[Nstr].length - 1; Nsmb++) {
            printf("%c", *(poem[Nstr].smb + Nsmb));
        }
    }
}
