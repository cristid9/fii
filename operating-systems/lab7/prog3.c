#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dir_walk(char *filename)
{
    struct stat stat_file;
    
    DIR *dir;
    struct dirent *dir_entry;

    if ((dir = opendir(filename)) == NULL) 
    {
        return;
    }

    while ((dir_entry = readdir(dir)) != NULL)
    {
        stat(filename, &stat_file);
        if (!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, ".."))
        {
            continue;
        }
        printf("%s\n", dir, dir_entry->d_name);
        
        if (S_ISDIR(stat_file.st_mode)) 
        {
            dir_walk(dir_entry->d_name);
        }
    }

    closedir(dir);
}

// finiish this shhit when you come ome

int main(int argc, char *argv[])
{
    dir_walk(".");

    return 0;
}
