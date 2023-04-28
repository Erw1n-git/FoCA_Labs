#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int Seconds_Diff_Count(char *time1, char *time2)
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

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: not enough arguments\n");
        return 1;
    }

    printf("[%d] *** SERVER HAS STARTED ***\n", getpid());

    char *time1 = argv[1];
    char *time2 = argv[2];

    printf("The difference in seconds between the two times is: %d\n", Seconds_Diff_Count(time1, time2));

    return 0;
}