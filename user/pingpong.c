#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char const *argv[])
{
    int pid;
    int p[2];
    pipe(p);

    if (fork() == 0) {
        char buf[2];
        pid = getpid();
        read(p[0], buf, 1);
        close(p[0]);
        printf("%d: received ping\n", pid);
        write(p[1], buf, 1);
        close(p[1]);
    } else {
        char buf[2];
        pid = getpid();
        write(p[1], buf, 1);
        close(p[1]);
        wait(0);
        read(p[0], buf, 1);
        close(p[0]);
        printf("%d: received pong\n", pid);
    }
	
	exit(0);
}