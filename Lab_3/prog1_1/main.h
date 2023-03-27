#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void readParams(int argc, char** argv);

void printHelpPage(char** argv);
void execBinary(char** argv);
void execBinaryAsync(char** argv);