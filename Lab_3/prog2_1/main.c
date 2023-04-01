#include "main.h"

void readParams(int argc, char **argv, char **time1, char **time2)
{
    if (argc < 3)
    {
        printf("(Error): Insufficient params number!\n");
        printf("Usage: \"%s: NN.NN.NN NN.NN.NN\" \n", argv[0]);
        exit(-1);
    }

    for (int i = 0; i < argc; i++)
    {
        if(i == 1) *time1 = argv[i];
        else *time2 = argv[i];
    }
    
}

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

int main(int argc, char **argv)
{
    char *time1 = NULL; 
    char *time2 = NULL;

    readParams(argc, argv, &time1, &time2);

    printf("Seconds difference between time1 and time2: %d\n", secondsDiffCount(time1, time2));

    return 0;
}