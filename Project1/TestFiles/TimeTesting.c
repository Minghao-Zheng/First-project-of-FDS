#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HeaderFiles/Algorithms.h"
clock_t start, stop;    /*  clock_t is the built-in type for processor time(ticks). */
double duration;    /*  records the time(seconds) of a function. */

void timeAlgorithm(int, int);
void printTimingTable(int *, int *, int *, double *, double *);

int main() {
    /*  V is input by the users, which indicates the maximum of the items. */
    int V;
    int sign;

    /*  If sign equals 1, then use algorithm 1.
        If 2, then use algorithm 2. 
        If other digits, then display error messages. */
    scanf("%d", &V);
    scanf("%d", &sign);
    if (sign != 1 && sign != 2) {
        printf("Error! Using illegal sign.\n");
    }
    /*  Test the time of algorithm1. 
        Generate a graph. */
    timeAlgorithm(V, sign);
}

void timeAlgorithm(int V, int sign) {
    /*  Showcase all the posiblities of n. */
    int n[8] = {1000, 5000, 10000, 20000, 
                40000, 60000, 80000, 100000};
    /*  We execute the function k[i] times. */
    int k[8] = {10000, 2500, 1000, 500, 250, 250, 100, 100};

    /*  ticks is the total ticks(microsecond).
        total time is the total second.
        dutation is one operation time in seconds. */
    int ticks[8] = {0};
    double total[8] = {0.0};
    double duration[8] = {0.0};
    /*  for every n, run n times. */
    for (int i = 0; i < 8; i++) {
        /*  N is the quantity of the items.
            a points to the array of all the items. 
            c records the sum. */
        int N = n[i];
        elementType *a;
        elementType c;

        a = (elementArray) malloc(N * sizeof(elementType));
        for (int i = 0; i < N; i++) {
            /*  Generate a truly random number as a[i], 
                which is no larger than V. */
            srand((unsigned)time(NULL));
            a[i] = rand() % V + 1;
        }
        /*  Generate a random number as c, which is no larger than 2V. */
        srand((unsigned)time(NULL));
        c = rand() % (2 * V) + 1;

        /*  clock() returns the amount of processor time(ticks) that has elapsed
            since the program began running. */
        start = clock();    /*  At the beginning of the function call. */
        for (int j = 0; j < k[i]; j++) {
            /*  Run the algorithm1 or algorithm2 k times.
                Determine call which function by sign. */
            if (sign == 1) {
                /*  The sign 0 means we don't want it print the result. */
                algorithm1(N, a, c, 0);
            } else {
                /*  The sign 0 means we don't want it print the result. */
                algorithm2(N, a, c, 0);
            } 
        }
        stop = clock();
        ticks[i] = stop - start;    /*  ticks records the ticks. */
        /*  CLK_TCK is a built-in constant, which indicates the ticks per second. */
        total[i] = ((double) (stop - start)) / CLK_TCK;
        duration[i] = total[i] / k[i];  /*  duration is the time per operation. */
        /*  free the memory. */
        free(a);
    }
    /*  At last, print the timing table. */
    printTimingTable(n, k, ticks, total, duration);
}
/*  The exquisite graph. */
void printTimingTable(int *n, int *k, int *ticks, double *total, double *duration) {
    printf("%12s %12s %12s %12s %12s\n", "N", "k", "ticks", "total", "duration");
    /*  The divider. */
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < 8; i++) {
        /*  Put out all the items to make the graph. */
        int N = n[i];
        int K = k[i];
        int tick = ticks[i];
        double totalSeconds = total[i];
        double durationSeconds = duration[i];
        printf("%12d %12d %12d %12.2f %12.5f\n", N, K, tick, totalSeconds, durationSeconds);
    }
}

