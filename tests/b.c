#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    int arr[] = {1, 2, 5, 4, 10, 3, 8};
    int arrSize = sizeof(arr) / sizeof(int);
    int start, end;
    int fd[2];

    if (pipe(fd) == -1)
        return (1);
    
    int id = fork();
    if (id == -1)
        return (2);
    
    if (id == 0)
    {
        start = 0;
        end = arrSize / 2;
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    int i;
    for (i = start; i < end; i++)
    {
        sum += arr[i];
    }

    printf("partial sum: %d\n", sum);
    
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    else
    {
        int sumchild;
        close(fd[1]);
        read(fd[0], &sumchild, sizeof(sumchild));
        close(fd[0]);

        int totalsum = sum + sumchild;
        printf("total sum: %d\n", totalsum);
        wait(NULL);
    }
}