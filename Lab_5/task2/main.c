#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_counter = 0;
pthread_mutex_t mutex;

void* increment_counter(void *arg)
{
    for(int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        shared_counter++;
        printf("THREAD[%ld]: Counter value is %d\n", (long)arg, shared_counter);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    int res;
    pthread_t thread[2];

    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0)
    {
        perror("Mutex initialization error!\n");
        exit(EXIT_FAILURE);
    }
    

    res = pthread_create(&thread[0], NULL, increment_counter, (void*)0);
    if (res != 0)
    {
        perror("Pthread creation error!\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&thread[1], NULL, increment_counter, (void*)1);
    if (res != 0)
    {
        perror("Pthread creation error!\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread[0], NULL);
    if (res != 0)
    {
        perror("Pthread join error!\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(thread[1], NULL);
    if (res != 0)
    {
        perror("Pthread join error!\n");
        exit(EXIT_FAILURE);
    }

    printf("Final counter value is %d\n", shared_counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}