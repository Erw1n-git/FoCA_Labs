#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int Is_Valid_Timestamp(const char *timestamp)
{
    if(strlen(timestamp) != 8) return 0;
    for(int i = 0; i < 8; ++i)
    {
        if(i == 2 || i == 5)
        {
            if(timestamp[i] != '.') return 0;
        }
        else 
        {
            if(timestamp[i] < '0' || timestamp[i] > '9') return 0;
        }
    }

    return 1;
}

int main() 
{
    char time1[9], time2[9];
    pid_t pid;
    int pipedes[2];
    pipe(pipedes);

    printf("[%d]*** CLIENT PROCESS HAS STARTED ***\n", getpid());
    printf("Enter two time stamps in a format NN.NN.NN \n");

    while(1)
    {
        printf("Time stamp 1: ");
        scanf("%8s%*[^\n]", time1);
        if(Is_Valid_Timestamp(time1)) break;
        else printf("*Error* Invalid timestamp format!\n");
    }

    while(1)
    {
        printf("Time stamp 2: ");
        scanf("%8s%*[^\n]", time2);
        if(Is_Valid_Timestamp(time2)) break; 
        else printf("*Error* Invalid timestamp format!\n");
    }

    printf("\n[%d]Starting server process...\n\n", getpid());

    if((pid = fork()) < 0)
    {
        printf("Fork error occured.\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipedes[0]);

        write(pipedes[1], time1, 9);
        write(pipedes[1], time2, 9);
        close(pipedes[1]);

        execl("./server", "server", time1, time2, NULL);
    } else {
        close(pipedes[1]);

        wait(NULL);
    }

    return 0;
}