/*
 * EXP-4: CPU Scheduling - Shortest Job First (Non-preemptive)
 * Selects the waiting process with the smallest execution time
 * to execute next.
 */
#include <stdio.h>

struct Process {
    int pid, bt, wt, tat;
    int completed;
};

int main() {
    int n, i, j, total = 0;
    struct Process p[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    int time = 0;
    for (i = 0; i < n; i++) {
        int idx = -1, min_bt = 999999;
        for (j = 0; j < n; j++) {
            if (!p[j].completed && p[j].bt < min_bt) {
                min_bt = p[j].bt;
                idx = j;
            }
        }
        p[idx].wt = time;
        time += p[idx].bt;
        p[idx].tat = time;
        p[idx].completed = 1;
        avg_wt += p[idx].wt;
        avg_tat += p[idx].tat;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
