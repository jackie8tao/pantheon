#include <stdio.h>
#include <unistd.h>

int main() {
    printf("linux daemon test\n");

    if (daemon(0, 0) < 0) {
        perror("daemon");
        return -1;
    }

    while (1) {
        printf("pid: %d\n", getpid());
    }
}

