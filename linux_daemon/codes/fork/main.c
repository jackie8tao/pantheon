#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>

int main() {
    printf("linux daemon test!\n");

    umask(0);

    pid_t pid = fork();
    if (-1 == pid) {
        perror("fork");
        return -1;
    }

    if (pid) {
        pid_t p_pid = getpid();
        printf("I'am father process, pid: %d, sid: %d\n", p_pid, getsid(p_pid));
        return 0;
    } else {
        pid_t c_pid = getpid();
        printf("I'am child process, pid:%d, sid:%d\n", c_pid, getsid(c_pid));
        if (-1 == setsid()) {
            perror("setsid");
            return -1;
        }
    }

    if (chdir("/") < 0) {
        perror("chdir");
        return -1;
    }

    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        perror("getrlimit");
        return -1;
    }

    rlim_t nfiles;
    nfiles = rl.rlim_cur > rl.rlim_max ? rl.rlim_max : rl.rlim_cur;
    for (rlim_t i = 3; i < nfiles; ++i) {
        close(i);
    }

    int fd;
    if ((fd = open("/dev/null", O_RDWR)) < 0) {
        perror("open");
        return -1;
    }

    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    while (1) {
        sleep(5);
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf(
                "now: %d-%d-%d %d:%d:%d\n",
                tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec
        );
    }
}