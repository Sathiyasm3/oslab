#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* arg) {
    char* name = (char*)arg;
    printf("Task %s started\n", name);
    sleep(2);
    printf("Task %s completed\n", name);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    printf("Multi-threaded program started\n");

    pthread_create(&thread1, NULL, task, "A");
    pthread_create(&thread2, NULL, task, "B");
    pthread_create(&thread3, NULL, task, "C");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("Multi-threaded program finished\n");
    return 0;
}

