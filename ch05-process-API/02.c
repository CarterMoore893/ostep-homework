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

/* I read the man pages for fork, which stated "The child inherits copies
   of the parent's set of open file descriptors **and description**
   This means that the two file descriptors share open file **status flags,
   file offset, and signal-driven I/O attributes**"
   
   This tells me that both the parent and child will have the fd open,
   but I don't think they will be able to write at the same time. At best,
   the scheduler will just pick a line to write first at worst, it'll crash.
*/

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
