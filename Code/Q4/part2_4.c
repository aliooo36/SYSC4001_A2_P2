#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define SLEEP 500000

typedef struct { // mem struct to hold variables
    int multiple;
    int counter;
} shared_data;

int main(void)
{
    int shmid = shmget(36, sizeof(shared_data), 0666); // get shared mem instance from part2_4 main file
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0); // attach the shared mem

    printf("P2 started (pid=%d, ppid=%d)\n", getpid(), getppid());
    printf("P2 waiting for counter to become %d\n", data -> counter);
    
    while (data->counter <= 100) {
        usleep(SLEEP);
    }
    
    printf("P2 counter starting\n");
    
    int local_counter = 0;
    unsigned long cycle = 0;
    while (data->counter <= 500) {
        if (local_counter % data->multiple == 0) {
            printf("P2 Cycle number: %lu - %d is a multiple of %d\n", cycle, local_counter, data->multiple);
        } else {
            printf("P2 Cycle number: %lu\n", cycle);
        }
        local_counter--;
        cycle++;
        usleep(SLEEP);
    }
    
    printf("P2 finished\n");
    shmdt(data); // detaches from shared mem
    return 0;
}
