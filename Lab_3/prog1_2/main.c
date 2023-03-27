#include "main.h"

void printParams(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("(Error): Insufficient params number!\n");
        exit(-1);
    }

    printf("Listing all given params...\n");
    for (int i = 0; i < argc; i++)
    {
        printf("Param(%d): %s\n", i, argv[i]);
    }
    printf("\n");
}

void printIDs(pid_t pid)
{
    printf("Listing ID\'s...\n");
    printf("PID: %d\n", pid);
    printf("SID: %d\n", getsid(pid));
    printf("PGID: %d\n", getpgid(pid));
    printf("PPID: %d\n", getppid());
    printf("\n");
}
 
void printUserName(uid_t uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);
    printf("User\'s name: %s\n", pwd->pw_name);
}

void printUserGroup(uid_t uid)
{
    struct group *grp;
    grp = getgrgid(uid);
    printf("User\'s group: (id)%d, (name)%s\n", grp->gr_gid, grp->gr_name);
}

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    uid_t uid = getuid();

    printParams(argc, argv);
    printIDs(pid);
    printUserName(uid);
    printUserGroup(uid);
    return 0;
}