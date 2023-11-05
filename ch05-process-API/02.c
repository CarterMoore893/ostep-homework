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
    // Per the book, close stdout. Idk if we need to do this unless I want
    // to reassign stdout to 02.output's FD. Can't I just fprintf?
    // Answer: nope! Per the printf man pages, I need to use dprintf()
    //close(STDOUT_FILENO);

    // Open a new stream
    int fd = open("./02.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    dprintf(fd, "Hello from pre-fork!\n");

    int rc = fork();
    dprintf(fd, "Hello from post-fork! I am %d\n", getpid());
    // On a fork, the PID of the child is returned to the parent,
    // and `0` is returned in the child.
    // On failure, -1 is returned in the parent and no child is created.
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        dprintf(fd, "Child %d->%d says hello!\n", getppid(), getpid());
    } else {
        // Parent execution
        dprintf(fd, "Parent %d says hello!\n", getpid());
    }  

    return EXIT_SUCCESS;
}
/* Answers:
   Yes, both the child and parent can access the fd.
   When each process attempts to write to the fd, the scheduler just picks one
*/
