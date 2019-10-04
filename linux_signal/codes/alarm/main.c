#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static time_t t;

static void
sig_alrm(int signo)
{
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    printf("%s", asctime(tm_info));
}

int
main(int argc, char **argv)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        perror("signal SIGALRM");
        return -1;
    }

    for (;;) {
        alarm(5);
        pause();
    }
}