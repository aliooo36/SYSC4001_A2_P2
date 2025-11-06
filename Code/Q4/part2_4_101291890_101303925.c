#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define SLEEP 500000

typedef struct { // struct to hold the variables in mem
    int multiple;
    int counter;
} shared_data;

int main(void)
{
    int shmid = shmget(36, sizeof(shared_data), IPC_CREAT | 0666); // create shared mem with key 36, size of shared_data variables and respective flags
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0); // attached shared mem

    data->multiple = 3; // mulitple to be tracked
    data->counter = 0; // init counter value

    pid_t pid = fork(); // intial child process creation

    if (pid < 0) {
        perror("fork failed");
        shmdt(data); // detach shared mem cause of error
        shmctl(shmid, IPC_RMID, NULL); // delete shared mem seg
        return 1;
    } else if (pid == 0) { // child (P2)
        shmdt(data); // detach shared mem piror to loading new program
        execlp("./part2_4_aux_101291890_101303925", "part2_4_aux_101291890_101303925", (char *)NULL);
        exit(1);
    } else { // parent (P1)
        printf("P1 started (pid=%d), child pid=%d\n", getpid(), pid);
        unsigned long cycle = 0;
        while (data->counter <= 500) {
            if (data->counter % data->multiple == 0) {
                printf("P1 Cycle number: %lu - %d is a multiple of %d\n", cycle, data->counter, data->multiple);
            } else {
                printf("P1 Cycle number: %lu\n", cycle);
            }
            data->counter++;
            cycle++;
            usleep(SLEEP);
        }
        printf("P1 finished\n");
        wait(NULL);
        printf("P2 done, exiting P1\n");
        
        shmdt(data); // parent detaches from shared mem
        shmctl(shmid, IPC_RMID, NULL); // delete the shared mem
    }
    return 0;
}