#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, int *argv[]) {
        if(argc < 1|| argc > 2){
                write(2, "An error has occured.\n", strlen("An error has occurred."));
                exit(EXIT_FAILURE);
        }
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd))!=NULL){
        printf("Current location: %s\n", cwd);
        }
}
