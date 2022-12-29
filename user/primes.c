#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn))
void
proc(int p[]) {
    int prime;
    int n;

    close(p[1]);
    read(p[0], &prime, 4);
    printf("prime %d\n", prime);

    int next = read(p[0], &n, 4);
    if (next) {
        int np[2];
        pipe(np);

        if (fork() == 0) {
            proc(np);
        } else {
            close(np[0]);
            if (n % prime != 0) {
                write(np[1], &n, 4);
            }
            while (read(p[0], &n, 4)) {
                if (n % prime != 0) {
                    write(np[1], &n, 4);
                }
            }
            close(np[1]);
            close(p[0]);
            wait(0);
        }
    }

    exit(0);
}

int 
main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);

    if (fork() == 0) {
        proc(p);
    } else {
        close(p[0]);
        for (int n = 2; n <= 35; n++) {
            write(p[1], &n, 4);
        }
        close(p[1]);
        wait(0);
    }
	
	exit(0);
}