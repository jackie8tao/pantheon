#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int 
main(int argc, char **argv)
{
    if (mkfifo("pipeB.log", 0666) < 0) {
        perror("mkfifo pipeB.log");
        return -1;
    }

    int fd;
    fd = open("pipeB.log", O_WRONLY|O_CREAT);
    if (fd < 0) {
        perror("open pipeB.log");
        return -1;
    }

    int ch;
    while((ch = getchar()) != EOF) {
        if (write(fd, &ch, 1) < 0) {
            perror("write");
            close(fd);
            return -1;
        }
    }
    
    close(fd);
    return 0;
}