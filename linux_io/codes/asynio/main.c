#include <stdio.h>
#include <aio.h>
#include <fcntl.h>

int 
main(int argc, char **argv)
{
    int fd;
    struct aiocb cb;
    fd = open("aio.txt", O_APPEND|O_CREAT|O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    return 0;
}