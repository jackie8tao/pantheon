#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void
sig_abrt(int signo)
{
    printf("signal SIGABRT handler\n");
    exit(0);
}

int
main(int argc, char **argv)
{
    if (signal(SIGABRT, sig_abrt) == SIG_ERR) {
        perror("signal SIGABRT");
        return -1;
    }

    abort();
    pause();
}