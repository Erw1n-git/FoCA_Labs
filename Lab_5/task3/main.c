#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 10

pthread_t thread[2];
char buffer[BUFFER_SIZE];
int read_index = 0, write_index = 0;
int buffer_count = 0;

pthread_mutex_t mutex;
pthread_cond_t buffer_not_full;
pthread_cond_t buffer_not_empty;

void* write_buffer(void *arg)
{
    for(int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&mutex);

        while(buffer_count == BUFFER_SIZE)
        {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        buffer[write_index] = 'A' + i;
        write_index++;
        write_index %= BUFFER_SIZE;
        buffer_count++;

        printf("Written value to buffer is %c\n", buffer[write_index-1]);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&buffer_not_empty);

        sleep(1);
    }

    return NULL;
}

void* read_buffer(void *arg)
{
    for(int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        while(buffer_count == 0)
        {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }

        printf("Read value from buffer is %c\n", buffer[read_index]);
        read_index++;
        read_index %= BUFFER_SIZE;
        buffer_count--;

        pthread_cond_signal(&buffer_not_full);

        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    return NULL;
}

int main()
{
    int res;

    res = pthread_mutex_init(&mutex, NULL);
    if(res != 0)
    {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_init(&buffer_not_full, NULL);
    if(res != 0)
    {
        perror("Pthread cond initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_cond_init(&buffer_not_empty, NULL);
    if(res != 0)
    {
        perror("Pthread cond initialization failed!\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread[0], NULL, write_buffer, NULL);
    if(res != 0)
    {
        perror("Thread creation failed!\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&thread[1], NULL, read_buffer, NULL);
    if(res != 0)
    {
        perror("Thread creation failed!\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread[0], NULL);
    if(res != 0)
    {
        perror("Thread join failed!\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(thread[1], NULL);
    if(res != 0)
    {
        perror("Thread join failed!\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);

    return 0;
}