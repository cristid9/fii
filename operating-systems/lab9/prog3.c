#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD_COUNT 10

int main()
{
    for (int i = 0; i < CHILD_COUNT; i++)
    {
        pid_t child_pid = fork();        
        if (child_pid == 0)
        {
            printf("Process %d\n", getpid());
            return 0;
        }
    }

    printf("Message from the parent");

    return 0;
}
