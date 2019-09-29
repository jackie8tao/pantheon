#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

static char buf[409600];

static void set_fl(int fd, int flags);
static void clr_fl(int fd, int flags);

int 
main(int argc, char **argv)
{
    int nread, nwrite, flags;
    char *ptr;

    nread = read(STDIN_FILENO, buf, sizeof(buf));
    if (-1 == nread) {
        perror("read");
        return -1;
    }
    
    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;
    while(nread > 0) {
        nwrite = write(STDOUT_FILENO, ptr, nread);
        fprintf(stderr, "write: %d, errno: %d\n", nwrite, errno);
        if (nwrite > 0) {
            ptr += nwrite;
            nread -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);

    return 0;
}

static void 
set_fl(int fd, int flags)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, NULL)) < 0) {
        perror("fcntl F_GETFL error");
        exit(-1);
    }

    val |= flags;
    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("fcntl F_SETFL error");
        exit(-1);
    }

    return;
}

static void 
clr_fl(int fd, int flags)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, NULL)) < 0) {
        perror("fcntl F_GETFL error");
        exit(-1);
    }

    val &= ~flags;
    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("fcntl F_SETFL error");
        exit(-1);
    }

    return;
}