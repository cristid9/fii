#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 100

static void child1Worker(int readPoint, int writePoint)
{
    int count;
    char buffer[BUFF_SIZE];

    while (0 < (count = read(readPoint, buffer, BUFF_SIZE)))
    {
        for (int i = 0; i < count; ++i)
        {
            if (buffer[i] >= 'a' && buffer[i] <= 'z')
                write(writePoint, &buffer[i], sizeof(char));
        }
    
    }

    close(readPoint);
    close(writePoint);
}

static void child2Worker(int readPoint, int writePoint)
{
    int count;
    char tmp;
    
    int freq[26];
    memset(freq, 0, sizeof(int) * 26);

    while (0 < (count = read(readPoint, &tmp, sizeof(char))))
    {
        freq[tmp - 'a']++;
    }

    close(readPoint);
    
    int fd = open("statistica.txt", O_CREAT|O_WRONLY, 0777);
    int diff = 0;
    char outputBuffer[BUFF_SIZE];

    for (int i = 0; i < 26; ++i)
    {
        if (freq[i] != 0)
        {
            sprintf(outputBuffer, "%c => %d\n", i + 'a', freq[i]);
            write(fd, outputBuffer, sizeof(outputBuffer));
            diff++;
        }
    }
    close(fd);

    write(writePoint, &diff, sizeof(int));

    close(writePoint);
}

static void parentWorker(int readPoint, int writePoint, const char* filename)
{
    int fd = open(filename, O_RDONLY);
    int count;
    char buffer[BUFF_SIZE];

    while (0 < (count = read(fd, buffer, BUFF_SIZE)))
    {
        write(writePoint, buffer, count);
    }

    close(writePoint);
    close(fd);

    int diff = -1;
    // I am aware that I forgot the error checking
    read(readPoint, &diff, sizeof(int));

    printf("Different characters: %d\n", diff);

    close(readPoint);
}

int main()
{
    int pipe1[2];

     int pipe2[2];
     int pipe3[2];

    if (pipe(pipe1) == -1)
    {  
        perror("Can't create pipe 1");
        exit(1);
    }
   
    if (pipe(pipe2) == -1)
    {  
        perror("Can't create pipe 2");
        exit(1);
    }

    if (pipe(pipe3) == -1)
    {  
        perror("Can't create pipe 3");
        exit(1);
    }

    pid_t child1 = fork();
    
    if (child1 == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[1]);
        close(pipe3[0]);
        
        child1Worker(pipe1[0], pipe2[1]);

        return 0;
    }
    
    pid_t child2 = fork();

    if (child2 == 0)
    {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        close(pipe3[0]);

        child2Worker(pipe2[0], pipe3[1]);
    
        return 0;
    }

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[1]);

    parentWorker(pipe3[0], pipe1[1], "date.txt");

    return 0;
}
