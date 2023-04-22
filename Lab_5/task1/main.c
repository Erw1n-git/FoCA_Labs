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
    pthread_t writerThread, readerThread;

    sem_init(&readSemaphore, 0, 0);
    sem_init(&writeSemaphore, 0, 1);

    pthread_create(&writerThread, NULL, writer, NULL);
    pthread_create(&readerThread, NULL, reader, NULL);

    pthread_join(writerThread, NULL);
    pthread_join(readerThread, NULL);

    sem_destroy(&readSemaphore);
    sem_destroy(&writeSemaphore);

    return 0;
}