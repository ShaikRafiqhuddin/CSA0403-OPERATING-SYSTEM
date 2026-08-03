/*
 * EXP-7: Non-preemptive Shortest Job First (SJF) algorithm
 * with process arrival times considered.
 */
#include <stdio.h>

int main() {
    int n, i, j, time = 0, completed = 0;
    int at[20], bt[20], wt[20], tat[20], done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    while (completed != n) {
        int idx = -1, min_bt = 999999;
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += bt[idx];
        tat[idx] = time - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = 1;
        completed++;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting Time\tTurnaround Time\n");
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
