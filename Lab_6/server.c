#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "./fifo_file"

int secondsDiffCount(char *time1, char *time2)
{
    int hours1, hours2, minutes1, minutes2, seconds1, seconds2, diff;

    hours1 = atoi(strtok(time1, "."));
    minutes1 = atoi(strtok(NULL, "."));
    seconds1 = atoi(strtok(NULL, "."));

    hours2 = atoi(strtok(time2, "."));
    minutes2 = atoi(strtok(NULL, "."));
    seconds2 = atoi(strtok(NULL, "."));

    diff = ((hours2 - hours1) * 3600) + ((minutes2 - minutes1) * 60) + (seconds2 - seconds1);

    return diff;
}

int main(int argc, char** argv)
{
    FILE* fifo;
    char time1[9];
    char time2[9];

    printf("*** SERVER HAS STARTED ***\n");
    printf("Waiting for client's input...\n");

    mkfifo(FIFO_NAME, 0600);

    fifo = fopen(FIFO_NAME, "r");
    if(fifo == NULL)
    {
        printf("*Error* Unable to open FIFO file.\n");
        exit(EXIT_FAILURE);
    }

    fgets(time1, 9, fifo);
    fgets(time2, 9, fifo);

    printf("The difference in seconds between the two times is: %d\n", secondsDiffCount(time1, time2));
    
    fclose(fifo);
    unlink(FIFO_NAME);

    return 0;
}