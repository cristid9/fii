#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


int main()
{
    int fd = open("fis.dat", O_RDWR);

    float t;
    read(fd, &t, sizeof(float));

    close(fd);

    printf("%f\n", t);



    return 0;
}
