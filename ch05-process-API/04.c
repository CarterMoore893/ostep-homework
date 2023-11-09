/* 04.c
   Chapter 5 problem 4
Task:  Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?*/

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
        scanf("What do you want to say?");
        printf("Child %d->%d says hello!\n", getppid(), getpid());
    }    return EXIT_SUCCESS;
}
/* Answers:
*/
