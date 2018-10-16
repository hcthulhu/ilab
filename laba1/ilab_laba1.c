#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int NPoints = 12;
const double L[3] = {0.2, 0.3, 0.5};
const double Lerr = 0.001;
const double Spp = 0.001035;
const double Derr = 0.1;
const double Dmt = 3.63;

int ReadData(double I[], double U[]);
void  CalculateLaba(double I[], double U[], double P[], double *Pavg, double Perr[], double *Perr_avg);
void WriteToFile(double P[], double Pavg, double Perr[], double Perr_avg);
double Dispersion(double X[], double Nfirst, double Nlast);
double Covariance(double X[], double Y[], double Nfirst, double Nlast);
double CheckData(double U[], double I[], double Pavg);


int main() {
    double* I = (double*)calloc(3 * NPoints, sizeof(double));
    double* U = (double*)calloc(3 * NPoints, sizeof(double));
    double P[3] = {}, Perr[3] = {}, Pavg = 0, Perr_avg = 0;

    int nMeas = ReadData(I, U);
    if (nMeas < NPoints * 3) {
        printf ("Incomplete Bxod.txt\n");
        return 1;
    }

    CalculateLaba(I, U, P, &Pavg, Perr, &Perr_avg);
    if (CheckData(U, I, Pavg) > 0) WriteToFile(P, Pavg, Perr, Perr_avg);

    free(I);
    free(U);

    return 0;
}


int ReadData(double I[], double U[]) {
    FILE* Bxod = fopen ("Bxod.txt", "r");
    if (!Bxod) {printf ("Can't open Bxod \n"); return -1;}
    int line = 0;
    for (;;) {
        if (fscanf (Bxod, "%lg %lg",  &I[line], &U[line]) == EOF)  break;
        line++;
    }
    fclose (Bxod);
    return line;
}


void CalculateLaba(double I[], double U[], double P[], double *Pavg, double Perr[], double *Perr_avg) {
    double R[3] = {}, Rerr[3] = {};
    double Nfirst = 0, Nlast = 0;
    double Perr_rel = 0;

    for (int LNum = 0; LNum <= 2; LNum++) {
        Nfirst = LNum * NPoints;
        Nlast = (LNum + 1) * NPoints - 1;
        R[LNum] = Covariance(U, I, Nfirst, Nlast)/Dispersion(I, Nfirst, Nlast);
        P[LNum] = 100 * Spp * R[LNum]/L[LNum];
        *Pavg += P[LNum];
    }
    *Pavg /= 3;

    for (int LNum = 0; LNum <= 2; LNum++) {
        Nfirst = LNum * NPoints;
        Nlast = (LNum + 1) * NPoints - 1;
        Rerr[LNum] = sqrt((Dispersion(U, Nfirst, Nlast)/Dispersion(I, Nfirst, Nlast) - (R[LNum] * R[LNum]))/(NPoints - 2));
        Perr_rel = sqrt((Rerr[LNum]/R[LNum]) * (Rerr[LNum]/R[LNum])
                   + (2 * Derr/Dmt) * (2 * Derr/Dmt) + (Lerr/L[LNum]) * (Lerr/L[LNum]));
        Perr[LNum] = P[LNum] * Perr_rel;
        *Perr_avg += Perr[LNum];
    }
    *Perr_avg /= 3;

}


double Dispersion(double X[], double Nfirst, double Nlast) {
    double Xdisp = 0, Xavg = 0;
    int line = 0;

    for ( line = Nfirst; line <= Nlast; line++ ) Xavg += X[line];
    Xavg /= NPoints;

    for ( line = Nfirst; line <= Nlast; line++ ) Xdisp += (X[line] - Xavg) * (X[line] - Xavg);
    Xdisp /= NPoints;

    return Xdisp;
}


double Covariance(double X[], double Y[], double Nfirst, double Nlast ) {
    double XYcov = 0, Xavg = 0, Yavg = 0, XYavg = 0;
    int line = 0;

    for ( line = Nfirst; line <= Nlast; line++ ) Yavg += Y[line];
    Yavg /= NPoints;


    for ( line = Nfirst; line <= Nlast; line++ ) Xavg += X[line];
    Xavg /= NPoints;

    for ( line = Nfirst; line <= Nlast; line++ ) XYavg += Y[line] * X[line];
    XYavg /= NPoints;

    XYcov = XYavg - Xavg * Yavg;

    return XYcov;
}

double CheckData(double U[], double I[], double Pavg) {
    for (int line = 0; line <= 3 * NPoints - 1; line++) {
        if (fabs((100 * Spp * U[line]/I[line])/L[(line)/NPoints] - Pavg) > Pavg/4) {
          printf("Check data in %i line\n", line + 1);
          return -1;
        }
    }
    return 1;
}

void WriteToFile(double P[], double Pavg, double Perr[], double Perr_avg) {
    FILE* Bixod = fopen ("Bixod.txt", "w");

    fprintf (Bixod, "=========================================================\n");
    fprintf (Bixod, "| L,m               |    %lg    |    %lg    |    %lg    |\n", L[0], L[1], L[2]);
    fprintf (Bixod, "|===================|===========|===========|===========|\n");
    fprintf (Bixod, "| p, 10^(-6)om*m    | %.3lg±%.1lg | %.3lg±%.1lg | %.3lg±%.1lg |\n", P[0], Perr[0], P[1], Perr[1], P[2], Perr[2]);
    fprintf (Bixod, "|===================|===================================|\n");
    fprintf (Bixod, "| p cp, 10^(-6)om*m |             %.3lg±%.1lg             |\n", Pavg, Perr_avg);
    fprintf (Bixod, "=========================================================\n");

    fclose (Bixod);
}
