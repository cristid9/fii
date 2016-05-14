#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// yea, ugly, I know.
void createProcessList(int current, int limit)
{
    if (current == limit)
        return;

    current++;
    pid_t child_pid = fork();
    if (-1 == child_pid)
    {
        perror("Couldn't create child process");
        exit(1);
    }

    if (child_pid == 0)
    {
        printf("Current %d child of %d\n", getpid(), getppid());
        createProcessList(current, limit);
        return;
    }

    wait(NULL);
}

int main()
{
    int limit;
    printf("Insert limit\n");
    scanf("%d", &limit);

    createProcessList(0, limit);

    return 0;
}
