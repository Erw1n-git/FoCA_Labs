#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <netdb.h>

#define BUF_SIZE 256

int Is_Valid_Timestamp(const char *timestamp)
{
    if (strlen(timestamp) != 8) return 0;
    for (int i = 0; i < 8; ++i)
    {
        if (i == 2 || i == 5)
        {
            if (timestamp[i] != '.') return 0;
        }
        else
        {
            if (timestamp[i] < '0' || timestamp[i] > '9') return 0;
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sock, port;
    char buf[BUF_SIZE];

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("*** CLIENT PROCESS HAS STARTED ***\n");

    port = atoi(argv[2]);

    printf("Creating socket...\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket create failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Looking for a host...\n");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        perror("look for a host failed!\n");
        exit(EXIT_FAILURE);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    serv_addr.sin_port = htons(port);

    printf("Connecting to the server...\n");
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect to server failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter two timestamps in a format NN.NN.NN \n");

    memset(buf, 0, BUF_SIZE);    
    while(1)
    {
        printf("Time stamp 1: ");
        scanf("%8s%*[^\n]", buf);
        if (Is_Valid_Timestamp(buf)) break;
        else printf("*Error* Invalid timestamp format!\n");
    }
    write(sock, buf, strlen(buf));

    memset(buf, 0, BUF_SIZE);
    while(1)
    {
        printf("Time stamp 2: ");
        scanf("%8s%*[^\n]", buf);
        if (Is_Valid_Timestamp(buf)) break;
        else printf("*Error* Invalid timestamp format!\n");
    }
    write(sock, buf, strlen(buf));

    close(sock);

    return 0;
}