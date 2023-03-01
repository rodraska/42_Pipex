#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1)
    {
        printf("Error ocurred opening pipe\n");
        return (1);
    }
    int id = fork();
    if (id == -1)
    {
        printf("Error ocurred with fork\n");
        return (4);
    }
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("Error ocurred writing to pipe\n");
            return (2);
        }
            
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("Error ocurred reading from pipe\n");
            return (3);
        }
        close(fd[0]);
        y *= 3;
        printf("from child: %d\n", y);
    }
    return (0);
}
