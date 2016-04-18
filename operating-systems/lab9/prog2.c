#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 100

int main()
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        exit(1);
    }

    if (child_pid == 0)
    {
        int numbers_fd = open("numbers.txt", O_RDWR);
        for (int i = 1; i <= N; i++)
        {
            write(numbers_fd, &i, sizeof(int));
        }

        close(numbers_fd);
        return 0;
    }

    pid_t child_pid2 = fork();

    if (child_pid2 == -1)
    {
        exit(1);
    }

    if (child_pid2 == 0)
    {
        
        int ops_fd = open("ops.txt", O_RDWR);
        char ops[] = {'+', '-', '*', '/'};
        for (int i = 0; i < (N / 2); i++)
        {
            write(ops_fd, &ops[i % 4], sizeof(char));
        }
        
        close(ops_fd);
        return 0;
    }

    int status1;
    int status2;

    wait(&status1);
    wait(&status2);

    // process the files;
    int numbers_fd = open("numbers.txt", O_RDWR);
    int ops_fd     = open("ops.txt", O_RDWR);

    int operand1, operand2;
    char operator;

    while (1)
    {
        
        int status = read(numbers_fd, &operand1, sizeof(int));
    
        if (status == 0 || status == -1)
        {
            perror("[1]Could not read anymore");
            break;
        }
        
        status = read(numbers_fd, &operand2, sizeof(int));
        
        if (status == 0 || status == -1)
        {
            perror("[2]Could not read anymore");
            break;
        }
       
        status = read(ops_fd, &operator, sizeof(char));
        if (status == -1)
        {
            printf("foo bar");
            exit(1);
        }
        int result = 0;
        switch (operator)
        {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0)
            { 
                perror("Could not divide by 0");
                exit(2);
            }    
            result = operand1 / operand2;
            break;
        }

        // Cu dedicatie pentru Marius Olaru
        printf("%d %c %d = %d\n", operand1, operator, operand2, result);
    }


    close(numbers_fd);
    close(ops_fd);

    return 0;
} 
