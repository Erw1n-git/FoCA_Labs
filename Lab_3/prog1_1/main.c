#include "main.h"

void readParams(int argc, char** argv)
{
	int c;
	
	while(1) 
	{
		c = getopt(argc, argv, "hw:f:");
		if(argc < 2)
		{
			printf("Use -h to seek help information\n");
			break;
		}
		if(c == -1) break;		

		switch(c)
		{
		case 'h':
			param_H(argv);
			break;
		case 'w':
			param_W(argv);
			break;
		case 'f':
			param_F(argv);
			break;
		}
	}
}

void param_H(char** argv)
{
	printf("Usage of %s:\n", argv[0]);
	printf("\t[-h] Print help page\n");
	printf("\t[-w \"name\"] Execute file from PATH variable\n");
	printf("\t[-f \"name\"] Execute file from PATH variable asynchronously\n");
}

void param_W(char** argv)
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
		printf("Executing file...\n\n");
		char *prog_name = optarg;
		execlp(prog_name, prog_name, NULL);
		printf("Error: exec failed\n");
        exit(EXIT_FAILURE);
	}
	default:
		wait(&rv);
		printf("\nThe exit code is: %d\n", rv);
		printf("Done.\n");
		break;
	}
}

void param_F(char** argv)
{
	pid_t pid;
	pid_t pid2;
	if((pid = fork()) < 0) exit (-1);
	if (pid == 0)
	{
		if((pid2 = fork()) < 0) exit (-1);
		if(pid2 == 0)
		{
			printf("Executing file asynchronously...\n");
			char *prog_name = optarg;
			execlp(prog_name, prog_name, NULL);
			printf("Error: exec failed\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("Immediately continuing program.\n");
			exit(0);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("Done.\n");
	}	
}

int main(int argc, char** argv)
{
	readParams(argc, argv);
	return 0;
}
