#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int 
main() 
{
    int fd = open("/var/run/pid.pid", O_RDWR | O_CREAT | O_APPEND);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    struct flock lk = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0
    };

    if (-1 == fcntl(fd, F_SETLK, &lk)) {
        perror("fcntl");
        return -1;
    }

    int n;
    char buf[BUFSIZ];
    if ((n = sprintf(buf, "%d\n", getpid())) < 0){
        perror("sprintf");
        return -1;
    }
    if (-1 == write(fd, buf, n)){
        perror("write");
        return -1;
    }

    for (;;) {

    }
}