#include "main.h"

void setupDaemon()
{
    pid_t pid;

    if((pid = fork()) < 0) 
    {
        printf("Fork error.\n");
        exit(-1);
    }

    if(pid != 0)
    {
        printf("(%d): Daemon started with pid \'%d\'\n", getpid(), pid);
        exit(0);
    }

    if(setsid() < 0)
    {
        printf("Setsid error.\n");
    }

    if(chdir("/") < 0)
    {
        printf("Chdir error.\n");
    }

    openlog("(GR: 222g, VAR: 13) ", LOG_PID, LOG_LOCAL0);

    struct rlimit flim;
    getrlimit(RLIMIT_NOFILE, &flim);
    for(rlim_t fd = 0; fd < flim.rlim_max; fd++)
    {
        close(fd);
    }

    syslog(LOG_INFO, "Daemon started with PID: %d", getpid());
}

void signalHandler(int signum)
{
    switch (signum)
    {
    case SIGUSR1:
        syslog(LOG_INFO, "Daemon caught USR1 (%d) signal.", signum);
        break;
    
    case SIGINT:
        syslog(LOG_INFO, "Daemon caught INT (%d) signal and stopped.", signum);
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    printf("(%d): Starting process as a daemon...\n", getpid());
    setupDaemon();

    signal(SIGUSR1, signalHandler);
    signal(SIGINT, signalHandler);

    for (; ;) pause();

    return 0;
}