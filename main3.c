#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_ITERATIONS 30
#define MAX_SLEEP 10

void ChildProcess() {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    int iterations = random() % MAX_ITERATIONS + 1;

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", pid);
        int sleep_time = random() % MAX_SLEEP + 1;
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, ppid);
    }
    printf("Child Pid: %d is done!\n", pid);
    exit(0);
}

int main() {
    pid_t child1, child2;

    
    srandom(time(NULL));

   
    child1 = fork();
    if (child1 < 0) {
        perror("Failed to fork child 1");
        exit(1);
    }

    if (child1 == 0) {
        ChildProcess();  
    } else {
       
        child2 = fork();
        if (child2 < 0) {
            perror("Failed to fork child 2");
            exit(1);
        }

        if (child2 == 0) {
            ChildProcess();  
        } else {
            int status;
            pid_t terminated_child;

            terminated_child = wait(&status);
            printf("Child Pid: %d has completed\n", terminated_child);

            terminated_child = wait(&status);
            printf("Child Pid: %d has completed\n", terminated_child);

            printf("Parent process is done!\n");
        }
    }

    return 0;
}
