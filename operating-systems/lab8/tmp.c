#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>


int main()
{
    int fd = open("fis.dat", O_RDWR);

    float t = 1.2;
    write(fd, &t, sizeof(float));

    close(fd);



    return 0;
}
