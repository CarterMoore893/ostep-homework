/* 03.c
   Chapter 5 problem 3
Task: Write another program using fork(). The child process should
   print “hello”; the parent process should print “goodbye”. You should
   try to ensure that the child process always prints first; can you do
   this without calling wait() in the parent?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("Hello from pre-fork!\n");

    int rc = fork();
    printf("Hello from post-fork! I am %d\n", getpid());
    // On a fork, the PID of the child is returned to the parent,
    // and `0` is returned in the child.
    // On failure, -1 is returned in the parent and no child is created.
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        printf("Child %d->%d says hello!\n", getppid(), getpid());
    } else {
        // Parent execution
        printf("Parent %d says goodbye!\n", getpid());
    }  

    return EXIT_SUCCESS;
}
/* Answers:
*/
