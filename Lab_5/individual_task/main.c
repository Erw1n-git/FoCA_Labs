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
    int res;
    pthread_t writerThread, readerThread;

    res = sem_init(&mutex, 0, 1);
    if (res != 0)
    {
        perror("sem_init error occured!\n");
        exit(EXIT_FAILURE);
    }
    
    res = sem_init(&empty, 0, N);
    if (res != 0)
    {
        perror("sem_init error occured!\n");
        exit(EXIT_FAILURE);
    }
    
    res = sem_init(&full, 0, 0);
    if (res != 0)
    {
        perror("sem_init error occured!\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&writerThread, NULL, writer, NULL);
    if (res != 0)
    {
        perror("pthread_create error occured!\n");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&readerThread, NULL, reader, NULL);
    if (res != 0)
    {
        perror("pthread_create error occured!\n");
        exit(EXIT_FAILURE);
    }
    

    res = pthread_join(writerThread, NULL);
    if (res != 0)
    {
        perror("pthread_join error occured!\n");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(readerThread, NULL);
    if (res != 0)
    {
        perror("pthread_join error occured!\n");
        exit(EXIT_FAILURE);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}