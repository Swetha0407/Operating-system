#include <stdio.h>
int main() {
    int at[10], bt[10], pr[10];
    int n, i, j, temp;
    int time = 0, over = 0, count, start;
    int sum_wait = 0, sum_turnaround = 0;
    float avgwait, avgturn;
    printf("Enter the number of processes (max 10):\n");
    scanf("%d", &n);
    if (n < 1 || n > 10) {
        printf("Invalid number of processes.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and execution time for process %d:\n", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        if (at[i] < 0 || bt[i] <= 0) {
            printf("Invalid arrival or execution time.\n");
            return 1;
        }
        pr[i] = i + 1;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;
            }
        }
    }
    printf("\nProcess | Arrival | Burst | Start | End | Waiting | Turnaround\n");
    while (over < n) {
        count = 0;
        for (i = over; i < n; i++) {
            if (at[i] <= time)
                count++;
            else
                break;
        }
        if (count > 1) {
            for (i = over; i < over + count - 1; i++) {
                for (j = i + 1; j < over + count; j++) {
                    if (bt[i] > bt[j]) {
                        temp = at[i];
                        at[i] = at[j];
                        at[j] = temp;
                        temp = bt[i];
                        bt[i] = bt[j];
                        bt[j] = temp;
                        temp = pr[i];
                        pr[i] = pr[j];
                        pr[j] = temp;
                    }
                }
            }
        }
        if (time < at[over])
            time = at[over];
        start = time;
        time += bt[over];
        printf("P[%d]    | %7d | %5d | %5d | %3d | %7d | %10d\n",
               pr[over], at[over], bt[over], start, time,
               start - at[over], time - at[over]);
        sum_wait += start - at[over];
        sum_turnaround += time - at[over];
        over++;
    }
    avgwait = (float)sum_wait / n;
    avgturn = (float)sum_turnaround / n;
    printf("\nAverage waiting time: %.2f\n", avgwait);
    printf("Average turnaround time: %.2f\n", avgturn);
    return 0;
}
