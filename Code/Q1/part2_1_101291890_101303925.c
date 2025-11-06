#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP 500000

int main(void)
{
    // inital parent process creation
    pid_t pid = fork();

    if (pid < 0)
    { // if pid isn't valid
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    { // child (P2)
        printf("p2 started (pid=%d, ppid=%d)\n", getpid(), getppid());
        int i = 0;
        while (1)
        {
            printf("p2: %d\n", i);
            i++;
            usleep(SLEEP);
        }
    }
    else
    { // parent (P1)
        printf("p1 started (pid=%d, child pid=%d)\n", getpid(), pid);
        int i = 0;
        while (1)
        {
            printf("p1: %d\n", i);
            i++;
            usleep(SLEEP);
        }
    }
    return 0;
}