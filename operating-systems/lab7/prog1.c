#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define OCC_SIZE 255
#define SECTOR 512

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: <prog> <filename>");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Oh snap, something wen wrong");
        exit(2);
    }
    

    int occurences[OCC_SIZE];
    memset(occurences, 0, sizeof(int) * OCC_SIZE);

    int buffer[2];

    int c;
    while (0 != (c = read(fd, buffer, 512)))
    {
        if (c == -1)
        {
            perror("Double snap, errors all over the place!");
            exit(3);
        }

        for (int i = 0; i < c; i++) {
            for (int match = 0; match < 255; match++)
            {
                /* This ma be redudant */
                if ((char)buffer[i] == (char)match)
                {
                    occurences[match]++;
                    break;
                }
            }
        }
    }

    for (int match = 0; match < 255; match++)
    {
        if (occurences[match] == 0)
        {
            continue;
        }
        printf("%c apare de %d ori \n", match, occurences[match]);
    }

    close(fd);

    return 0;
}
