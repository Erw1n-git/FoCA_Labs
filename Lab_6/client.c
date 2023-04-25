#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIFO_NAME "./fifo_file"

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

int main(int argc, char** argv)
{
    FILE* fifo;
    char time1[9];
    char time2[9];

    printf("*** CLIENT PROCESS HAS STARTED ***\n");
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

    fifo = fopen(FIFO_NAME, "w");
    if(fifo == NULL)
    {
        printf("*Error* Unable to open a FIFO.\n");
        exit(EXIT_FAILURE);
    }
    
    fputs(time1, fifo);
    fputs(time2, fifo);
    fflush(fifo);
    fclose(fifo);

    unlink(FIFO_NAME);

    return 0;
}
