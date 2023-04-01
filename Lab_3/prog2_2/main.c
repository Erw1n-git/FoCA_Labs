#include "main.h"

int main(int argc, char **argv)
{
    char path[] = "../prog2_1/./prog_2_1";

    pid_t pid;
    int rv;

    printf("\n(%d): Running child process for \'prog_2_1\'...\n", getpid());

    switch (pid=fork())
    {
    case -1:
        perror("fork error\n");
		exit(1);
        break;
    case 0:
    {
        printf("(%d): Executing file \'prog_2_1\'...\n\n", getpid());
		execv(path, argv);
		printf("(%d) Error: exec failed.\n* Make sure file \'%s\' exists.\n", getpid(), path);
        exit(EXIT_FAILURE);
    }
    default:
        wait(&rv);
        printf("\n(%d): Parent process finished.\n", getpid());
        break;
    }


    return 0;
}