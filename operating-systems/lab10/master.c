#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define OP_SIZE 30

int main(int argc, char* argv[])
{
    int operand1, operand2;
    char operator;
    
    int read = 0;

    do 
    {
        printf("Introdu 2 numere si un operator: \n");
        scanf("%d %d %c", &operand1, &operand2, &operator);

        int status;
        pid_t child_pid = fork();
        
        printf("iiiResult :%d\n",child_pid);
        if (child_pid == -1)
        {
            perror("N-am putut crea procesul");
        }

        if (child_pid == 0)
        {
            
            printf("in proesul copil");
            char storage_operand1[OP_SIZE];

            char storage_operand2[OP_SIZE];
            char storage_op[2];

            storage_op[0] = operator;
            storage_op[1] = '\0';

            snprintf(storage_operand1, OP_SIZE, "%d", operand1);
            snprintf(storage_operand2, OP_SIZE, "%d", operand2);

            execl("slave", "slave", storage_operand1, storage_operand2, 
                  storage_op, NULL);
            
            perror("N-am putut face operatia");
            return 1;
        }

        wait(&status);

        char res = WEXITSTATUS(status);
        printf("Result :<%d>\n", res);
        
        printf("Mai faci si alte calcule? (Tasteaza 1 daca da)\n");
        scanf("%d", &read);
    
    }
    while (read == 1);


    return 0;
}
