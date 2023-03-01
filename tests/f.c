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

//2 processes
//child generates random numbers and sends to parent
//parent receives and sums numbers


int main(int ac, char **av)
{
    int fd[2];
    if (pipe(fd) == -1)
        return (2);
    int pid = fork();
    if (pid == -1)
        return (1);
    
    if (pid == 0)
    {
        close(fd[0]);
        int n, i;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("generated: ");
        for (i = 0; i < n; i++)
        {
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");
        if (write(fd[1], &n, sizeof(int)) < 0)
            return (4);
        printf("n sent: %d\n", n);
        if (write(fd[1], arr, sizeof(int) * n) < 0)
            return (3);
        printf("sent array\n");
        close (fd[1]);
    }
    else
    {
        close(fd[1]);
        int arr[10];
        int n, i, sum = 0;
        if (read(fd[0], &n, sizeof(int)) < 0)
            return (5);
        if (read(fd[0], arr, sizeof(int) * n) < 0)
            return (6);
        printf("received array\n");
        close (fd[0]);
        for (i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        printf("result: %d\n", sum);
        wait(NULL);
    }
}