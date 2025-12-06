#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[10][10], max[10][10], need[10][10];
    int available[10];
    int finish[10] = {0};
    int safeSeq[10];

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources (%d values):\n", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate Need Matrix = Max - Allocation
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Apply Banker's Safety Algorithm
    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {

            if (finish[i] == 0) {
                int canAllocate = 1;

                // Check if need <= available for all resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                // If process can be allocated
                if (canAllocate) {
                    for (int k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is in an UNSAFE STATE.\n");
            return 0;
        }
    }

    // Safe Sequence
    printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
