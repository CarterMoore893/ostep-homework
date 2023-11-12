/* 04.c
   Chapter 5 problem 4
Task:  Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?*/
#define _GNU_SOURCE // Needed for execvpe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // execl
    printf("(%d) Parent started\n", getpid());
    int rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        my_args[0] = "/bin/ls";
        my_args[1] = "-l";
        printf("(%d) execl\n", getpid());
        execl(my_args[0], my_args[1], NULL);
        // Nothing beyond this line will execute for this Child
        printf("I will not execute!\n");
    }
    wait(&rc);

    // execlp
    rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        my_args[0] = strdup("ls");
        my_args[1] = strdup("");
        printf("(%d) execlp\n", getpid());
        execlp(my_args[0], my_args[1], NULL);
    }
    wait(&rc);

    // execle
    rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        my_args[0] = "/usr/bin/ls";
        my_args[1] = "l";
        char* my_env[2];
        my_env[0] = "/usr/bin";
        printf("(%d) execle\n", getpid());
        execle(my_args[0], my_args[1], NULL, my_env);
    }
    wait(&rc);

    // execv
    rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        my_args[0] = "/usr/bin/ls";
        printf("(%d) execv\n", getpid());
        execv(my_args[0], my_args);
    }
    wait(&rc);

    // execvp
    rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        my_args[0] = "ls";
        printf("(%d) execvp\n", getpid());
        execvp(my_args[0], my_args);
    }
    wait(&rc);

    // execvpe
    rc = fork();
    if (rc == -1) {
        fprintf(stderr, "(EE) %d fork failed\n", getpid());
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process executes here
        char* my_args[3];
        char* my_environ[2];
        my_args[0] = "ls";
        my_args[1] = "-l";
        my_environ[0] = "/usr/bin";
        my_environ[1] = "/bin";
        printf("(%d) execvpe\n", getpid());
        execvpe(my_args[0], my_args, my_environ);
    }
    wait(&rc);
    printf("(%d) Done\n", getpid());
    return EXIT_SUCCESS;
}
/* Answers:
*/
