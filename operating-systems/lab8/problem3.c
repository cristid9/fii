#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[])
{
    int          fd, codRead, codBlocaj;
    char         ch;
    struct flock lacat;

    /* verificarea existentei argumentului in linia de comanda */
    if(argc < 2)
    {
        fprintf(stderr,"Programul trebuie apelat cu cel putin un parametru.\n");
        exit(1);
    }

    /* deschiderea fisierului de date */
    if(-1 == (fd = open("fis.dat", O_RDWR)) )
    { /* trateaza cazul de eroare la deschidere */
        perror("Nu pot deschide fisierul fis.dat deoarece ");
        exit(2);
    }

    int argIdx;
    for (argIdx = 1; argIdx < argc; argIdx++)
    {
        /* pregatirea lacatului pentru fisier */
        lacat.l_type   = F_WRLCK;
        lacat.l_whence = SEEK_SET;
        lacat.l_start = 0;
        lacat.l_len    = sizeof(float); /* aici se poate pune orice valoare, inclusiv 0,
                               deoarece pentru problema noastra nu conteaza lungimea zonei blocate.*/

        while( (-1 == (codBlocaj = fcntl(fd,F_SETLK,&lacat)) ) && ((errno == EACCES)||(errno == EAGAIN)) )
        { 
            fprintf(stderr, "Blocaj imposibil [ProcesID:%d].\n", getpid());
            perror("\tMotivul");
            sleep(6);
        }
        if(codBlocaj == -1)
        {
            fprintf(stderr,"Eroare unknown la blocaj [ProcesID:%d].\n", getpid());
            perror("\tMotivul");
            exit(3);
        }
        float tmp = atof(argv[argIdx]);
        float storage;
        read(fd, &storage, sizeof(float));
        lseek(fd, 0, SEEK_SET);
        tmp += storage;
        write(fd, &tmp, sizeof(float));
        printf("Am scris %f\n", tmp);

        lacat.l_type   = F_UNLCK;
        lacat.l_whence = SEEK_SET;
        lacat.l_start  = 0;
        lacat.l_len    = sizeof(float); 
    }

    close(fd);
    return 0;
}
