#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char cmd[] = "/usr/bin/ls";
    char *av[] = {"ls", "-la", NULL};
    char *env[] = {NULL};

    printf("start of execve call: %s\n", cmd);
    if (execve(cmd, av, env) == -1)
        perror("could not execute execve");
    printf("something went wrong\n");
}