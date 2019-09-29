#include <unistd.h>
#include <stdio.h>

static char buf[64];

int 
main(int argc, char **argv)
{
    int n;
    while((n = read(STDIN_FILENO, buf, 64)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            perror("write");
            return -1;
        }
    }

    if (n < 0) {
        perror("read");
        return -1;
    }

    return 0;
}
