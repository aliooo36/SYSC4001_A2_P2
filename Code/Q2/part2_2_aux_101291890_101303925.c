#include <stdio.h>
#include <unistd.h>

#define SLEEP 500000

int main(void)
{
    printf("P2 started (pid=%d, ppid=%d)\n", getpid(), getppid());
    int counter = 0;
    unsigned long cycle = 0;
    while (1)
    {
        if (counter % 3 == 0)
        { // counter logic
            printf("P2 Cycle number: %lu - %d is a multiple of 3\n", cycle, counter);
        }
        else
        {
            printf("P2 Cycle number: %lu\n", cycle);
        }
        counter--; // decrement for Process 2
        cycle++;
        usleep(SLEEP);
    }
    return 0;
}