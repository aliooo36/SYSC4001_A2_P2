#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SLEEP 500000

typedef struct {
    int multiple;
    int counter;
} shared_data;

void sem_wait(int semid) {
    struct sembuf sb; // need this to access buffer variables
    sb.sem_num = 0;  // since we only have one set
    sb.sem_op = -1;  // decrement S
    sb.sem_flg = 0;  // if -1, block
    semop(semid, &sb, 1); // perform the op
}

void sem_signal(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;   // increment S
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

int main(void)
{
    int shmid = shmget(36, sizeof(shared_data), 0666);
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0);
    int semid = semget(36, 1, 0666);
 
    printf("P2 started (pid=%d, ppid=%d)\n", getpid(), getppid());
    printf("P2 waiting for counter > %d\n", data->counter);
    
    while (1) {
        sem_wait(semid);
        int current = data->counter;
        sem_signal(semid);
        
        if (current > 100) break;
        usleep(SLEEP);
    }
    
    int local_counter = 0;
    unsigned long cycle = 0;
    while (1) {
        sem_wait(semid); // locking to get correct reading on variable
        int current = data->counter;
        sem_signal(semid);
        
        if (current > 500) break;
        
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
    shmdt(data);
    return 0;
}
