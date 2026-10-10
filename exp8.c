#include <stdio.h>
int main() {
    int i, NOP, quant;
    int at[10], bt[10], temp[10];
    int ct[10] = {0};
    int time = 0, completed = 0;
    int wt = 0, tat = 0;
    float avg_wt, avg_tat;
    printf("Total number of processes (max 10): ");
    scanf("%d", &NOP);
    if (NOP < 1 || NOP > 10) {
        printf("Invalid number of processes.\n");
        return 1;
    }
    for (i = 0; i < NOP; i++) {
        printf("\nEnter arrival time for Process[%d]: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for Process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        if (at[i] < 0 || bt[i] <= 0) {
            printf("Invalid arrival or burst time.\n");
            return 1;
        }
        temp[i] = bt[i];
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quant);
    if (quant <= 0) {
        printf("Time quantum must be positive.\n");
        return 1;
    }
    while (completed < NOP) {
        int executed = 0;
        for (i = 0; i < NOP; i++) {
            if (temp[i] > 0 && at[i] <= time) {
                executed = 1;
                if (temp[i] <= quant) {
                    time += temp[i];
                    temp[i] = 0;
                    ct[i] = time;
                    completed++;
                }
                else {
                    temp[i] -= quant;
                    time += quant;
                }
            }
        }
        if (!executed && completed < NOP) {
            time++;
        }
    }
    printf("\nProcess\tArrival\tBurst\tTAT\tWaiting\n");
    for (i = 0; i < NOP; i++) {
        int turnaround = ct[i] - at[i];
        int waiting = turnaround - bt[i];
        tat += turnaround;
        wt += waiting;
        printf("P[%d]\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], turnaround, waiting);
    }
    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    return 0;
}
