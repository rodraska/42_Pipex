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
    int pid = fork();
    if (pid == -1)
        return (1);
    
    if (pid == 0)
    {
        while (1)
        {
            printf("some text\n");
            usleep(50000);
        }
    }
    else
    {
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }
}