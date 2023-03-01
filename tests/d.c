#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int ac, char **av)
{
    int p1[2]; //child to parent
    int p2[2]; //parent to child

    if (pipe(p1) == -1)
        return (1);
    if (pipe(p2) == -1)
        return (1);
    
    int pid = fork();
    if (pid == -1)
        return (2);
    if (pid == 0)
    {
        close(p1[0]);
        close(p2[1]);
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1)
            return (3);
        printf("received %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1)
            return (4);
        printf("wrote %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1)
            return (5);
        printf("wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1)
            return (6);
        printf("result is %d\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
}