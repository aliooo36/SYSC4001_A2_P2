#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP 500000

int main(void)
{
    // inital parent process creation
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    { // child (P2)
        // Replace child with the separate program
        execlp("./part2_2_aux_101291890_101303925", "part2_2_aux_101291890_101303925", (char *)NULL);
        exit(1);
    }
    else
    { // parent (P1)
        printf("P1 started (pid=%d), child pid=%d\n", getpid(), pid);
        int counter = 0;
        unsigned long cycle = 0;
        while (1)
        {
            if (counter % 3 == 0)
            {
                printf("P1 Cycle number: %lu - %d is a multiple of 3\n", cycle, counter);
            }
            else
            {
                printf("P1 Cycle number: %lu\n", cycle);
            }
            counter++;
            cycle++;
            usleep(SLEEP);
        }
    }
    return 0;
}