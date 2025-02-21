#include <stdio.h>
#include <unistd.h>

void task(char* name, int delay) {
    printf("Task %s started\n", name);
    sleep(delay);
    printf("Task %s completed\n", name);
}

int main() {
    printf("Single-threaded program started\n");

    task("A", 2);
    task("B", 3);
    task("C", 1);

    printf("Single-threaded program finished\n");
    return 0;
}

