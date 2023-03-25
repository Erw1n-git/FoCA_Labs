#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void readParams(int argc, char** argv);

void param_H(char** argv);
void param_W(char** argv);
void param_F(char** argv);