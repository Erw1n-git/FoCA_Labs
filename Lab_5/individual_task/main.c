#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

const int N = 10;

int buffer[N];
int in = 0, out = 0;
sem_t mutex, empty, full;

void *writer(void *arg) {
    int item;

    while (1) {
        item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        in = (in + 1) % N;

        printf("writer:  %d\n", item);

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *reader(void *arg) {
    int item;

    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        out = (out + 1) % N;

        printf("reader: %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t writerThread, readerThread;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_create(&writerThread, NULL, writer, NULL);
    pthread_create(&readerThread, NULL, reader, NULL);

    pthread_join(writerThread, NULL);
    pthread_join(readerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}