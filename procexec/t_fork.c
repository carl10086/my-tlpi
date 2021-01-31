//
// Created by carl on 2021/1/31.
//
#include "../lib/tlpi_hdr.h"
#include <sys/wait.h>

static int idata = 111; // static field allocated in text segments

int main(int argc, char *argv[]) {
    printf("hello world\n");

    int istack = 222; // stack field

    pid_t childPid;

    pid_t waitPid;
    // change fork -> vfork , see istack and idata changed in parent process ;
    switch (childPid = fork()) {
        case -1:
            errExit("fork");
        case 0:
            printf("c---> now in child process, begin to sleep\n");
            sleep(3);
            idata += 2;
            istack += 1;
            printf("c---> in child: sleep finished,  pid=%ld , istack=%d, idata = %d\n", childPid, istack, idata);
            break;
        default:
            /*Give child chance to execute*/
            // sleep(3); // if not sleep , child go dead ... main process exit first ...
            waitPid = wait(NULL);
            if (waitPid == -1) {
                if (errno == ECHILD) {
                    printf("No more children - bye!\n");
                    exit(EXIT_SUCCESS);
                } else {
                    errExit("wait");
                }
            }

            printf("in parent: pid=%ld , istack=%d, idata = %d\n", childPid, istack, idata);
            break;
    }

    /*BOTH parent and child go here*/
//    printf("now pid is %ld\n", childPid);
    exit(EXIT_SUCCESS);


}