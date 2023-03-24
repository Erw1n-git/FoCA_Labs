#include "main.h"

int main(int argc, char** argv)
{
	bool isFirst = true;
	int c;
	
	while(1) 
	{
		c = getopt(argc, argv, "hw:f:");
		if(c == -1 && isFirst)
		{
			printf("Use -h to seek help information\n");
			break;
		}
		if(c == -1) break;		

		switch(c)
		{
		case 'h':
			printf("Usage of %s:\n", argv[0]);
			printf("\t[-h] Print help page\n");
			printf("\t[-w \"name\"] Execute file from PATH variable\n");
			printf("\t[-f \"name\"] Execute file from PATH variable asynchronously\n");
			break;
		case 'w':
			printf("envoked -w with param: %s\n", optarg);
			break;
		case 'f':
			printf("envoked -f with param: %s\n", optarg);
			break;
		}

		isFirst = false;
	}
	return 0;
}
