#include "main.h"

void readParams(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("Use -h to seek help information\n");
		exit(-1);
	}

	int c;
	while(1) 
	{
		c = getopt(argc, argv, "hw:f:");
		if(c == -1) break;		

		switch(c)
		{
		case 'h':
			printHelpPage(argv);
			break;
		case 'w':
			execBinary(argv);
			break;
		case 'f':
			execBinaryAsync(argv);
			break;
		}
	}
}

void printHelpPage(char** argv)
{
	printf("Usage of %s:\n", argv[0]);
	printf("\t[-h] Print help page\n");
	printf("\t[-w \"name\"] Execute file from PATH variable\n");
	printf("\t[-f \"name\"] Execute file from PATH variable asynchronously\n");
}

void execBinary(char** argv)
{
	pid_t pid;
	int rv; 
	switch (pid=fork())
	{
	case -1:
		perror("fork error");
		exit(1);
		break;
	case 0:
	{
		printf("(%d): Executing file...\n", getpid());
		execlp(optarg, optarg, NULL);
		printf("(%d) Error: exec failed.\n", getpid());
        exit(EXIT_FAILURE);
	}
	default:
		wait(&rv);
		printf("\n(%d): The exit code is: %d", getpid(), rv);
		break;
	}
}

void execBinaryAsync(char** argv)
{
	pid_t pid;
	pid_t pid2;
	if((pid = fork()) < 0) exit (-1);
	if (pid == 0)
	{
		if((pid2 = fork()) < 0) exit (-1);
		if(pid2 == 0)
		{
			printf("(%d, 2nd child process): Executing file asynchronously...\n", getpid());
			char *prog_name = optarg;
			execlp(prog_name, prog_name, NULL);
			printf("(%d) error: exec failed\n", pid2);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("(%d, 1st child process): Immediately continuing program...\n", getpid());
			printf("(%d, 1st child process): Sleeping for 1 second...\n", getpid());
			sleep(1);
			printf("(%d, 1st child process): Finishing process...\n", getpid());
			exit(0);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}	
}

int main(int argc, char** argv)
{
	printf("(%d): PID of initial process.\n\n", getpid());
	readParams(argc, argv);
	printf("\n(%d): Done.\n", getpid());
	return 0;
}
