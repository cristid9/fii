#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Based on the professor's checker script, this shit works...
void spawnNodes(int curLevel, int levelLimit, int childrenNumber, 
                int nodeNumber, int offset)
{
    printf("%d-%d\n", getpid(), getppid());

    if (curLevel == levelLimit)
    {
        exit(0);
    }

    curLevel++;
    for (int i = 0; i < childrenNumber; i++)
    {
        pid_t childPid = fork();
        if (childPid == -1)
        {
            perror("Couldn't create process");
            exit(1);
        }

        if (childPid == 0)
        {
            spawnNodes(curLevel, levelLimit, childrenNumber, offset + i, 
                       offset + i);
            break;
        }
    }
    for (int i = 0; i < childrenNumber; i++)
        wait(NULL);
}

int main()
{
    int levelLimit, children;
    scanf("%d %d", &levelLimit, &children);

    spawnNodes(0, levelLimit, children, 0, 0);

    return 0;
}
