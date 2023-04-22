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
    pthread_t thread[2];

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread[0], NULL, increment_counter, (void*)0);
    pthread_create(&thread[1], NULL, increment_counter, (void*)1);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    printf("Final counter value is %d\n", shared_counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}