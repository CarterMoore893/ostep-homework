/* 01.c
   Chapter 5 problem 1
Task: Write a program that calls fork(). Before calling fork(), have the
    main process access a variable (e.g., x) and set its value to some-
    thing (e.g., 100). What value is the variable in the child process?
    What happens to the variable when both the child and parent change
    the value of x?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int x = 100;
    printf("(NN) Main process %d assigned x: %d\n", getpid(), x);

    int rc = fork();
    // On a fork, the PID of the child is returned to the parent,
    // and `0` is returned in the child.
    // On failure, -1 is returned in the parent and no child is created.

    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        printf("(NN) %d child x: %d\n", getpid(), x);
    } else {
        // Parent execution
        printf("(NN) %d parent x: %d\n", getpid(), x);
    }

    return EXIT_SUCCESS;
}
