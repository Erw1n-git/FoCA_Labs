#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const char* FILE_NAME = "shared.txt";

sem_t readSemaphore, writeSemaphore;

void *writer(void *arg) {
    FILE *file;

    for (int i = 1; i <= 10; i++) {
        sem_wait(&writeSemaphore);

        file = fopen(FILE_NAME, "a");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        fprintf(file, "This is line %d.\n", i);
        fclose(file);

        printf("Writer thread wrote line %d.\n", i);
        sem_post(&readSemaphore);

        sleep(1);
    }
    return NULL;
}

void *reader(void *arg) {
    FILE *file;
    char line[256];

    for (int i = 1; i <= 10; i++) {
        sem_wait(&readSemaphore);

        file = fopen(FILE_NAME, "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        int line_number = 0;
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (line_number == i) {
                printf("Reader thread read line %d: %s\n", i, line);
                break;
            }
        }
        fclose(file);

        sem_post(&writeSemaphore);

        sleep(1);
    }
    return NULL;
}

int main() {
    int res;
    pthread_t writerThread, readerThread;
    
    res = sem_init(&readSemaphore, 0, 0);
    if (res != 0)
    {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
    
    res = sem_init(&writeSemaphore, 0, 1);
    if (res != 0)
    {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
    

    res = pthread_create(&writerThread, NULL, writer, NULL);
    if (res != 0)
    {
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&readerThread, NULL, reader, NULL);
    if (res != 0)
    {
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }
    

    res = pthread_join(writerThread, NULL);
    if (res != 0)
    {
        perror("Error joining thread");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(readerThread, NULL);
    if (res != 0)
    {
        perror("Error joining thread");
        exit(EXIT_FAILURE);
    }
    

    sem_destroy(&readSemaphore);
    sem_destroy(&writeSemaphore);

    return 0;
}