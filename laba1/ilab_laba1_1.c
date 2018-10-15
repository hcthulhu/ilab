#include <stdio.h>

const int NPoints = 100;
const double L[3] = {0.2, 0.3, 0.5};
const double Spp = 0.001035;

int ReadData(double** I, double** U);
void Calculatelaba(double** I, double** U, double p[]);
void WriteToFile(double p[]);
double dispersion(double** I);
double covariance(int column, double** U, double** I);


int main() {
    double* I = NULL;
    double* U = NULL;
    double p[3] = {};
    FILE* Bxod = fopen ("Bxod.txt", "r");
    if (!Bxod) {printf ("Can't open Bxod\n"); return -1;}
    int line = 0;
    *I = calloc (NPoints, sizeof(double));
    *U = calloc (NPoints, sizeof(double));
    for (;;) {
        if (fscanf (Bxod, "%lg %lg %lg %lg",  *(I + line), *(U + line * 3), *(U + line * 3 + 1), *(U + line * 3 + 2)) == EOF)  break;
        line++;
      }
    //int nMeas = ReadData(&I, &U);
  //  if (nMeas <= 0) return 1;
    for (int line = 0; line <=11; line++ ) printf ("%lg/n", *(I+line));

    /*Calculatelaba(&I, &U, p);
    WriteToFile(p);*/

    return 0;
}


int ReadData(double** I, double** U) {
    FILE* Bxod = fopen ("Bxod.txt", "r");
    if (!Bxod) {printf ("Can't open Bxod\n"); return -1;}
    int line = 0;
    *I = (double**)calloc (NPoints, sizeof(double));
    *U = (double**)calloc (NPoints, sizeof(double));
    for (;;) {
        if (fscanf (Bxod, "%lg %lg %lg %lg",  *(I + line), *(U + line * 3), *(U + line * 3 + 1), *(U + line * 3 + 2)) == EOF)  break;
        line++;
    }
    fclose (Bxod);
    return line;
}

/*
void Calculatelaba(double** I, double** U, double p[]) {
    double R[3] = {};
    for (int LNum = 0; LNum <= 2; LNum++) {
        R[LNum] = covariance(LNum, &U, &I)/dispersion(&I);
        p[LNum] = 100 * Spp * R[LNum]/L[LNum];
    }
}


double dispersion(double** I) {
    double Idisp = 0, Iavg = 0;
    int line = 0;

    for ( line = 0; line <=11; line++ ) Iavg += *(I + line);
    Iavg = Iavg/line;

    for ( line = 0; line <=11; line++ ) Idisp += (*(I + line) - Iavg) * (*(I + line) - Iavg));
    Idisp /= line;

    return Idisp;
}


double covariance( int LNum, double** U, double** I ) {
    double UIcov = 0, Uavg = 0, Iavg = 0, UIavg = 0;
    int line = 0;

    for ( line = 0; line <=11; line++ ) Iavg += *(I + line);
    Iavg /= line;

    for ( line = 0; line <=11; line++ ) Uavg += *(U + line * 3 + LNum);
    Uavg /= line;

    for ( line = 0; line <=11; line++ ) UIavg += (*(I + line)) * (*(U + line * 3 + LNum));
    UIavg /= line;

    UIcov = UIavg - Uavg * Iavg;

    return UIcov;
}

void WriteToFile(double p[]) {
    FILE* Bixod = fopen ("Bixod.txt", "w");

    fprintf (Bixod, "==========================================\n");
    fprintf (Bixod, "| L,m               | %lg  | %lg  | %lg  |\n", L[0], L[1], L[2]);
    fprintf (Bixod, "|===================|======|======|======|\n");
    fprintf (Bixod, "| p, 10^(-6)om*m    | %.3lg | %.3lg | %.3lg |\n", p[0], p[1], p[2]);
    fprintf (Bixod, "|===================|====================|\n");
    fprintf (Bixod, "| p cp, 10^(-6)om*m |        %.3lg        |\n", (p[0] + p[1] + p[2])/3);
    fprintf (Bixod, "==========================================\n");

    fclose (Bixod);
}
*/
