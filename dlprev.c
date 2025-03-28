#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_RESOURCES 3

pthread_mutex_t resource[NUM_RESOURCES];

void* process(void* arg) {
    int id = *(int*)arg;

    printf("Process %d attempting to acquire resources...\n", id);

    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_mutex_lock(&resource[i]);
        printf("Process %d acquired resource %d.\n", id, i);
    }

    printf("Process %d is executing with all resources.\n", id);

    for (int i = NUM_RESOURCES - 1; i >= 0; i--) {
        pthread_mutex_unlock(&resource[i]); 
        printf("Process %d released resource %d.\n", id, i);
    }

    printf("Process %d finished execution.\n", id);

    free(arg);
    return NULL;
}

int main() {
    pthread_t processes[NUM_RESOURCES];

    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_mutex_init(&resource[i], NULL); 
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&processes[i], NULL, process, id);
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_join(processes[i], NULL);
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_mutex_destroy(&resource[i]);
    }

    return 0;
}
