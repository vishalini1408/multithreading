#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdio.h>

void *task(void *arg) {
    printf("Thread %ld time-sliced on single core\n", (long)arg);
    return NULL;
}

int main(void) {
    pthread_t t[4];
    cpu_set_t cpu;

    CPU_ZERO(&cpu);
    CPU_SET(0, &cpu);

    for (long i = 0; i < 4; i++)
        pthread_create(&t[i], NULL, task, (void *)(i + 1));

    for (int i = 0; i < 4; i++) {
        pthread_setaffinity_np(t[i], sizeof(cpu_set_t), &cpu);
        pthread_join(t[i], NULL);
    }

    return 0;
}
