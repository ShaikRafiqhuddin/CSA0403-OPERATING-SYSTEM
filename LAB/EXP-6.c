/*
 * EXP-6: CPU Scheduling - Preemptive Priority Scheduling
 * Lower priority number = higher priority.
 */
#include <stdio.h>

int main() {
    int n, i, j, time = 0, completed = 0;
    int bt[20], pr[20], rem_bt[20], wt[20], tat[20], at[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rem_bt[i] = bt[i];
    }

    int done[20] = {0};
    while (completed != n) {
        int idx = -1, best_pr = 999999;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0 && pr[i] < best_pr) {
                best_pr = pr[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rem_bt[idx]--;
        time++;

        if (rem_bt[idx] == 0) {
            completed++;
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }
    }

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], pr[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
