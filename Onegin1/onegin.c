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
char getcode (char smb);
int compare (const string* a, const string* b);
void SortData1 (string* poem, int StrAmt);
void SortData2 (string* poem, int StrAmt);

int main() {
    string* poem = NULL;
    char* SolidTXT = NULL;
    int SmbAmt = 0;
    int StrAmt = 0;

    ReadData(&poem, &SolidTXT, &SmbAmt, &StrAmt);
    SortData1(poem, StrAmt);
    SortData2(poem, StrAmt);

    free(poem);
    free(SolidTXT);
}

int ReadData(string** poem, char** SolidTXT, int* SmbAmt, int* StrAmt) {
    FILE* hamlet = fopen ("hamlet.txt", "r");
    if ( !hamlet ) {printf ("Can't open hamlet.txt\n"); return -1;}

    struct stat st = {};
    stat ("hamlet.txt", &st);
    *SmbAmt = (int)st.st_size;

    *SolidTXT = (char*)calloc(*SmbAmt, sizeof(char));
    fread(*SolidTXT, sizeof(char), *SmbAmt, hamlet);

    *poem = (string*)calloc(MaxStr, sizeof(string));
    (*poem)->smb = *SolidTXT;

    int Nstr = 0;
    for ( int cntr = 0, str_lengh = 0; cntr <= *SmbAmt; cntr++ ) {
        str_lengh++;
        if ( *(*SolidTXT + cntr) == '\n' ) {
            (*poem + Nstr + 1)->smb = (*SolidTXT + cntr + 1);
            (*poem + Nstr)->length = str_lengh;
            str_lengh = 0;
            Nstr++;
        }
    }

    *StrAmt = Nstr;
    *poem = (string*)realloc(*poem, (Nstr)*sizeof(string));

    fclose (hamlet);
    return 1;
}

void WriteToFile(string* poem, int StrAmt) {
    for ( int Nstr = 0; Nstr <= StrAmt; Nstr++ ) {
        for ( int Nsmb = 0; Nsmb <= poem[Nstr].length - 1; Nsmb++ ) {
            printf("%c", *(poem[Nstr].smb + Nsmb));
        }
    }
}

char getcode (char smb) {
    if ( (smb >= 'A') && (smb <= 'Z') )
        return smb + 32;
    if ( smb == '\n' )
        return 1;
    return smb;
}

int compBegin (const string* a, const string* b) {
    int i = 0, j = 0;
    if ( (a->length - 1 == 0) && (b->length - 1 != 0) )
        return 1;
    if ( (a->length - 1 != 0) && (b->length - 1 == 0) )
        return -1;
    if ( (a->length - 1 == 0) && (b->length - 1 == 0) )
        return 0;
    for ( ; (i <= a->length - 1) && (j <= b->length - 1); ) {
        if ( ((*(a->smb + i) >= ' ') && (*(a->smb + i) < 'A')) ||
             ((*(a->smb + i) > 'Z')  && (*(a->smb + i) < 'a' )) ||
             ((*(a->smb + i) > 'z')  && (*(a->smb + i) <= '~')) ) {
                i++;
                continue;
        }
        if ( ((*(b->smb + j) >= ' ') && (*(b->smb + j) < 'A')) ||
             ((*(b->smb + j) > 'Z')  && (*(b->smb + j) < 'a' )) ||
             ((*(b->smb + j) > 'z')  && (*(b->smb + j) <= '~')) ) {
                j++;
                continue;
        }
        if ( getcode(*(a->smb + i)) > getcode(*(b->smb + j)) ) {
            return 1;
        }
        if ( getcode(*(a->smb + i)) < getcode(*(b->smb + j)) ) {
            return -1;
        }
        i++;
        j++;
    }
    return 0;
}

int compEnd (const string* a, const string* b) {
    int i = a->length - 1, j = b->length - 1;
    if ( (i == 0) && (j != 0) )
        return 1;
    if ( (i != 0) && (j == 0) )
        return -1;
    if ( (i == 0) && (j == 0) )
        return 0;
    for ( ; (i >= 0) && (j >= 0); ) {
        if ( ((*(a->smb + i) >= ' ') && (*(a->smb + i) < 'A')) ||
             ((*(a->smb + i) > 'Z')  && (*(a->smb + i) < 'a' )) ||
             ((*(a->smb + i) > 'z')  && (*(a->smb + i) <= '~')) ) {
                i--;
                continue;
        }
        if ( ((*(b->smb + j) >= ' ') && (*(b->smb + j) < 'A')) ||
             ((*(b->smb + j) > 'Z')  && (*(b->smb + j) < 'a' )) ||
             ((*(b->smb + j) > 'z')  && (*(b->smb + j) <= '~')) ) {
                j--;
                continue;
        }
        if ( getcode(*(a->smb + i)) > getcode(*(b->smb + j)) ) {
            return 1;
        }
        if ( getcode(*(a->smb + i)) < getcode(*(b->smb + j)) ) {
            return -1;
        }
        i--;
        j--;
    }
    return 0;
}


void SortData1 (string* poem, int StrAmt) {
    qsort(poem, StrAmt, sizeof(string), (int(*) (const void *, const void *)) compBegin);
    FILE* sort1 = fopen ("SortBegin.txt", "w");

    for ( int Nstr = 0; Nstr <= StrAmt; Nstr++ ) {
        for ( int Nsmb = 0; Nsmb <= poem[Nstr].length - 1; Nsmb++ ) {
            fprintf(sort1, "%c", *(poem[Nstr].smb + Nsmb));
        }
    }
    fclose(sort1);
}

void SortData2 (string* poem, int StrAmt) {
    qsort(poem, StrAmt, sizeof(string), (int(*) (const void *, const void *)) compEnd);
    FILE* sort2 = fopen ("SortEnd.txt", "w");

    for ( int Nstr = 0; Nstr <= StrAmt; Nstr++ ) {
        for ( int Nsmb = 0; Nsmb <= poem[Nstr].length - 1; Nsmb++ ) {
            fprintf(sort2, "%c", *(poem[Nstr].smb + Nsmb));
        }
    }
    fclose(sort2);
}
