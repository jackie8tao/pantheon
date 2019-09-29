#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ch;
    char *dir = "";
    char *cmd = "";

    while ((ch = getopt(argc, argv, "d:c:")) != -1) {
        switch (ch) {
            case 'd':
                dir = optarg;
                break;
            case 'c':
                cmd = optarg;
                break;
            default:
                printf("-d and -c are must specify\n");
        }
    }

    // 目录是否为空
    if (!strlen(dir)) {
        fprintf(stderr, "chroot directory is empty\n");
        return -1;
    }

    // 命令是否为空
    if (!strlen(cmd)) {
        fprintf(stderr, "command is empty\n");
        return -1;
    }

    int ret;
    ret = chroot(dir);
    if (ret) {
        fprintf(stderr, "chroot: %s\n", strerror(errno));
        return errno;
    }

    ret = chdir("/");
    if (ret) {
        fprintf(stderr, "chdir: %s\n", strerror(errno));
        return errno;
    }

    ret = system(cmd);
    if (ret) {
        fprintf(stderr, "execute %s error: %d\n", cmd, ret);
        return -1;
    }

    return 0;
}

