/*
 * EXP-8: CPU Scheduling - Round Robin Scheduling Algorithm
 */
#include <stdio.h>

int main() {
    int n, tq, i, time = 0;
    int bt[20], rem_bt[20], wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int remaining = n;
    while (remaining > 0) {
        int done_this_round = 1;
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done_this_round = 0;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                    remaining--;
                }
            }
        }
        if (done_this_round) break;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
