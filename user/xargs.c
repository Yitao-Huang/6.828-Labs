#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    char *xargs[MAXARG];

    for (int i = 1; i < argc; i++) {
        xargs[i-1] = argv[i];
    }

    char buf[512];
    int index = argc-1;
    int n = 0;
    int endl = 0;

    while (read(0, buf+n, 1) != 0) {
        if (buf[n] == '\n') {
            endl = 1;
        }
        if (buf[n] == ' ' || buf[n] == '\n') {
            buf[n] = '\0';
            xargs[index++] = buf;
            n = 0;
        }
        n++;

        if (endl) {
            endl = 0;
            xargs[index] = 0;
            index = argc-1;

            if (fork() == 0) {
                exec(xargs[0], xargs);
            } else {
                wait(0);
            }
        }
    }

	exit(0);
}