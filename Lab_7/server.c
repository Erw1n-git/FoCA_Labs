#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUF_SIZE 256

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

int main(int argc, char **argv)
{
    struct sockaddr_in serv_addr, cli_addr;
    int sock, newsock, port;
    socklen_t clen;
    char buf[BUF_SIZE];

    char time1[9];
    char time2[9];

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("*** SERVER PROCESS HAS STARTED ***\n");

    printf("Creating socket...\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket create failed!\n");
        exit(EXIT_FAILURE);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    port = atoi(argv[1]);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    printf("Binding to socket...\n");
    if (bind(sock, (struct sockaddr*)&serv_addr, 
        sizeof(serv_addr)) < 0)
    {
        perror("socket bind failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Listening to socket...\n");
    listen(sock, 1);
    clen = sizeof(cli_addr);

    newsock = accept(sock, (struct sockaddr*)&cli_addr, &clen);
    if (newsock < 0)
    {
        perror("newsock accept failed!\n");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0, BUF_SIZE);
    read(newsock, buf, BUF_SIZE-1);
    buf[BUF_SIZE] = 0;
    strcpy(time1, buf);

    memset(buf, 0, BUF_SIZE);
    read(newsock, buf, BUF_SIZE-1);
    buf[BUF_SIZE] = 0;
    strcpy(time2, buf);

    printf("\nThe difference in seconds between timestamps: %d\n", Seconds_Diff_Count(time1, time2));


    close(newsock);
    close(sock);

    return 0;
}