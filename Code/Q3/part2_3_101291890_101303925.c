#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SLEEP 500000

int main(void)
{
    // inital parent process creation
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) { // child (P2)
        // Replace child with the separate program
        execlp("./part2_3", "part2_3", (char *)NULL);
        exit(1);
    } else { // parent (P1)
        printf("P1 started (pid=%d), child pid=%d\n", getpid(), pid);
        wait(NULL);
        printf("P2 done, exiting P1\n");
    }
    return 0;
}