#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <unistd.h>

#define EVSIZ 2

static int epfd;
static struct epoll_event evs[EVSIZ];

static struct epoll_event  
epoll_setfd(const char *path)
{
    int fd;
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    struct epoll_event ev = {
        .events = EPOLLIN | EPOLLET,
        .data = {.fd = fd}
    };

    return ev;
}

static void 
close_fd()
{
    int fd;
    for (int i=0; i<EVSIZ; ++i) {
        fd = evs[i].data.fd; 
        if (fd != 0) {
            close(fd);
        }
    }
    close(epfd);
}

int 
main(int argc, char **argv)
{
    epfd = epoll_create(EVSIZ);
    if (epfd < 0) {
        perror("epoll_create");
        return -1;
    }
    evs[0] = epoll_setfd("pipeA.log");
    evs[1] = epoll_setfd("pipeB.log");

    epoll_ctl(epfd, EPOLL_CTL_ADD, evs[0].data.fd, &evs[0]);
    epoll_ctl(epfd, EPOLL_CTL_ADD, evs[1].data.fd, &evs[1]);

    int idx, n, fd;
    char buf[1024];
    while (1)
    {
        idx = epoll_wait(epfd, evs, EVSIZ, 5000);
        if (idx < 0) {
            perror("epoll_wait");
            continue;
        }

        if (idx == 0) {
            continue;
        }

        fd = evs[idx-1].data.fd;
        if ((n = read(fd, buf, sizeof(buf))) < 0) {
            perror("read");
            close_fd();
            return -1;
        } else {
            if (n >= sizeof(buf)) {
                // 忽略超过缓冲区大小的内容
                continue;
            }

            buf[n] = '\0';
            printf("%s", buf);
            for (int i=0; i<n; ++i) {
                buf[i] = '\0';
            }
        }
    }

    close_fd();
    return 0;
}