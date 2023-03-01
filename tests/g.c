#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

int main(int ac, char **av)
{
    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    
    int pid = fork();
    if (pid < 0)
        return (2);
    
    if (pid == 0)
    {
        close(fd[0]);
        char str[200];
        printf("input string: ");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';
        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) < 0)
            return (4);
        if (write(fd[1], str, sizeof(char) * n) < 0)
            return (3);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char str[200];
        int n;

        if (read(fd[0], &n, sizeof(int)) < 0)
            return (6);
        if (read(fd[0], str, sizeof(char) * n) < 0)
            return (7);
        printf("received: %s\n", str);
        close(fd[0]);
        wait(NULL);
    }
    return (0);
}