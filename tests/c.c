#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int ac, char **av)
{
    if (mkfifo("myfifo1", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("could not create fifo file\n");
            return (1);
        }
    }

    printf("opening...\n");
    int fd = open("myfifo1", O_RDWR);
    printf("opened\n");
    int x = 67;
    if (write(fd, &x, sizeof(x)) == -1)
    {
        printf("error writing to fd\n");
        return (2);
    }
    printf("written\n");
    close(fd);
    printf("closed\n");
    return (0);
}