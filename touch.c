#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{       
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const  char *pathname;
    if(argc != 2){
        write(2, "Invalid number of arguments.\n", strlen("Invalid number of arguments.\n"));
        return -1;
    }
    if(strcmp(argv[0],"touch")){
        pathname=argv[1];
        fd = creat(pathname,mode);
        if (fd<0){
            write(2, "Cannot create file.\n", strlen("Cannot create file.\n"));
            return -1;
        }
    }
}
           

