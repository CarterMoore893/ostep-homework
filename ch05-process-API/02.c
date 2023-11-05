/* 02.c
   Chapter 5 problem 2
Task: Write a program that opens a file (with the open() system call)
   and then calls fork() to create a new process. Can both the child
   and parent access the file descriptor returned by open()? What
   happens when they are writing to the file concurrently, i.e., at the
   same time?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int rc = fork();
    // On a fork, the PID of the child is returned to the parent,
    // and `0` is returned in the child.
    // On failure, -1 is returned in the parent and no child is created.

    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
    } else {
        // Parent execution
    }  

    return EXIT_SUCCESS;
}
