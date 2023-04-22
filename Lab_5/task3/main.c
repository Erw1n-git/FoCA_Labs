#include <stdio.h>
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
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&buffer_not_full, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);
    pthread_create(&thread[0], NULL, write_buffer, NULL);
    pthread_create(&thread[1], NULL, read_buffer, NULL);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);

return 0;
}

/* Ця програма реалізує зчитування та запис даних спільний буфер з допомогою двох потоків.

У головному потоці створюються два допоміжних потоки write_buffer та read_buffer.

write_buffer потік заповнює буфер даними. Для цього він 
за допомогою м'ютекса блокує доступ інших потоків до буферу. 

Якщо буфер заповнений, потік очікує на сигнал від потоку, що зчитує дані з буферу. 
Якщо буфер не заповнений, потік записує нові дані в буфер, 
використовуючи наступний індекс запису, який зберігається у змінній write_index. 
Потім потік сигналізує про те, що буфер не порожній за 
допомогою pthread_cond_signal(&buffer_not_empty) і звільняє м'ютекс.

read_buffer потік зчитує дані з буфера. Для цього він також блокує доступ інших 
потоків до буферу за допомогою м'ютекса. Якщо буфер порожній, потік очікує на 
сигнал від потоку, що записує дані в буфер. Якщо буфер не порожній, потік зчитує дані з буферу, 
використовуючи наступний індекс зчитування, який зберігається у змінній read_index. 
Потім потік сигналізує про те, що буфер не заповнений за допомогою pthread_cond_signal(&buffer_not_full)
 і звільняє м'ютекс.

Кожен потік затримується на певний час, 
щоб можна було відслідкувати зміну стану буфера під час роботи програми.

Після завершення роботи допоміжних потоків м'ютекси і умовні змінні звільняються.

*/


