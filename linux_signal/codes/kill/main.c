#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void
sig_usr(int signo)
{
    if (signo == SIGUSR1) {
        printf("signal SIGUSR1\n");
    }
    return;
}

int
main(int argc, char **argv)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("signal SIGUSR1");
        return -1;
    }

    for (;;) {
        sleep(5);
        kill(getpid(), SIGUSR1);
    }
}