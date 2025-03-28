#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void calculateNeed(int processes, int resources, int max[][resources], int allocation[][resources], int need[][resources]) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes, int resources, int allocation[][resources], int need[][resources], int available[]) {
    bool finish[processes];
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    int work[resources];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < processes) {
        bool progressMade = false;

        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canFinish = true;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    count++;
                    progressMade = true;
                    break;
                }
            }
        }

        if (!progressMade) {
            return false;
        }
    }

    return true;
}

void requestResources(int processes, int resources, int allocation[][resources], int need[][resources], int available[], int process, int request[]) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded maximum claim.\n");
            return;
        }
        if (request[i] > available[i]) {
            printf("Resources are not available.\n");
            return;
        }
    }

    int originalAvailable[resources];
    int originalAllocation[processes][resources];
    int originalNeed[processes][resources];

    for (int i = 0; i < resources; i++) {
        originalAvailable[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            originalAllocation[i][j] = allocation[i][j];
            originalNeed[i][j] = need[i][j];
        }
    }

    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe(processes, resources, allocation, need, available)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied.\n");
        for (int i = 0; i < resources; i++) {
            available[i] = originalAvailable[i];
        }

        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                allocation[i][j] = originalAllocation[i][j];
                need[i][j] = originalNeed[i][j];
            }
        }
    }
}

int main() {
    int processes, resources;
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &processes, &resources);

    int allocation[processes][resources];
    int max[processes][resources];
    int need[processes][resources];
    int available[resources];

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed(processes, resources, max, allocation, need);

    int process;
    int request[resources];
    printf("Enter process number and resource request:\n");
    scanf("%d", &process);
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }

    requestResources(processes, resources, allocation, need, available, process, request);

    return 0;
}
