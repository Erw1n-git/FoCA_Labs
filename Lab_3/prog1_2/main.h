#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

void printParams(int argc, char **argv);
void printIDs(pid_t pid);
void printUserName(uid_t uid);
void printUserGroup(uid_t uid);