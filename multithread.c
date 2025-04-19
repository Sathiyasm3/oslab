#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep()

#define NUM_THREADS 5

pthread_mutex_t lock;

void* print_count(void* thread_id) {
    long tid = (long) thread_id;

    pthread_mutex_lock(&lock);
    printf("Thread %ld is starting...\n", tid);
    pthread_mutex_unlock(&lock);

    sleep(1);  // Simulate some work

    pthread_mutex_lock(&lock);
    printf("Thread %ld is ending...\n", tid);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    long t;

    pthread_mutex_init(&lock, NULL);

    printf("Main: Program started\n");

    for (t = 0; t < NUM_THREADS; t++) {
        if (pthread_create(&threads[t], NULL, print_count, (void*)t)) {
            printf("Error: Unable to create thread %ld\n", t);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Main: All threads have finished.\n");
    return 0;
}
