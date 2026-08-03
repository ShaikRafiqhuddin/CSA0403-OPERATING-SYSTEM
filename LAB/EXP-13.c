/*
 * EXP-13: Implementation of various memory allocation strategies -
 * First Fit, Best Fit and Worst Fit (menu driven).
 */
#include <stdio.h>

int main() {
    int bsize[20], psize[20], bno, pno, i, j;
    int allocation[20];
    int choice;

    printf("Enter number of blocks: ");
    scanf("%d", &bno);
    printf("Enter sizes of the blocks:\n");
    for (i = 0; i < bno; i++)
        scanf("%d", &bsize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &pno);
    printf("Enter sizes of the processes:\n");
    for (i = 0; i < pno; i++)
        scanf("%d", &psize[i]);

    printf("\nChoose allocation strategy:\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter choice: ");
    scanf("%d", &choice);

    for (i = 0; i < pno; i++)
        allocation[i] = -1;

    int temp[20];
    for (i = 0; i < bno; i++) temp[i] = bsize[i];

    for (i = 0; i < pno; i++) {
        int best_idx = -1;

        if (choice == 1) { /* First Fit */
            for (j = 0; j < bno; j++) {
                if (temp[j] >= psize[i]) { best_idx = j; break; }
            }
        } else if (choice == 2) { /* Best Fit */
            for (j = 0; j < bno; j++) {
                if (temp[j] >= psize[i]) {
                    if (best_idx == -1 || temp[j] < temp[best_idx]) best_idx = j;
                }
            }
        } else if (choice == 3) { /* Worst Fit */
            for (j = 0; j < bno; j++) {
                if (temp[j] >= psize[i]) {
                    if (best_idx == -1 || temp[j] > temp[best_idx]) best_idx = j;
                }
            }
        }

        if (best_idx != -1) {
            allocation[i] = best_idx;
            temp[best_idx] -= psize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < pno; i++) {
        printf("P%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
