
#include "types.h"
#include "user.h"

int main() {

    int returnPid, exitStatus;
    int i;
    int pid_a[5];
    for (i = 0; i <5; i++) {
        sleep(5);
        pid_a[i] = fork();

        if (pid_a[i] == 0) {
            printf(1, "PID: %d\n", getpid());
                exit(3);
        }
    }

   sleep(50);
    printf(1, "Waiting for PID: %d to exit\n",pid_a[0]);
    returnPid = waitpid(pid_a[0], &exitStatus, 0);
	 printf(1, "PID: %d exited with exit status %d\n",returnPid, exitStatus);

    printf(1, "Waiting for PID: %d to exit\n",pid_a[1]);
    returnPid = waitpid(pid_a[1], &exitStatus, 0);
    printf(1, "PID: %d exited with exit status %d\n",returnPid, exitStatus);

    printf(1, "Waiting for PID: %d to exit\n",pid_a[2]);
    returnPid = waitpid(pid_a[2], &exitStatus, 0);
    printf(1, "PID: %d exited with exit status %d\n",returnPid, exitStatus);

    printf(1, "Waiting for PID: %d to exit\n",pid_a[3]);
    returnPid = waitpid(pid_a[3], &exitStatus, 0);
    printf(1, "PID: %d exited with exit status %d\n",returnPid, exitStatus);

    printf(1, "Waiting for PID: %d to exit\n",pid_a[4]);
    returnPid = waitpid(pid_a[4], &exitStatus, 0);
    printf(1, "PID: %d exited with exit status %d\n",returnPid, exitStatus);
    exit(0);

         	                                                                                                                                                                
exit(0);

}
