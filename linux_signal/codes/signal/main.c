#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void 
sig_usr(int signo)
{
    if (signo == SIGUSR1) {
        printf("received SIGUSR1\n");
    } else if(signo == SIGUSR2) {
        printf("received SIGUSR2\n");
    }

    return;
}

int 
main(int argc, char **argv)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("signal SIGUSR1");
        return 0;
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("signal SIGUSR2");
        return 0;
    }

    for(;;) {
        pause();
    }
}