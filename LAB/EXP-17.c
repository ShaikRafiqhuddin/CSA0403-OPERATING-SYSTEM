/*
 * EXP-17: Deadlock avoidance using Banker's Algorithm.
 */
#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[20][20], max[20][20], avail[20], need[20][20];

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[20] = {0}, safeSeq[20];
    int work[20];
    for (j = 0; j < m; j++) work[j] = avail[j];

    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) { canRun = 0; break; }
                }
                if (canRun) {
                    for (j = 0; j < m; j++) work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state (deadlock may occur).\n");
    }

    return 0;
}
