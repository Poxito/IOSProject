#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{       
if(argc != 1){
    write(2, "Too much arguments. \n", strlen("Too much arguments.\n"));
    return -1;
}
if(strcmp(argv[0],"help")){
    printf("CD \t --- Move to another location.\n");
    printf("LS \t --- Check available items and locations.\n");
    printf("PWD \t --- Check your current location.\n");
    printf("CAT \t --- Interact with an item.\n");
    printf("TOUCH \t --- Create an item.\n");
    printf("MV \t --- Move an item to another location.\n");
    printf("CP \t --- Make a copy of an item.\n");
    printf("GREP \t --- Search for desired word on an item.\n");
    printf("MAN \t --- Show detailed information about a command.\n");
}
}
           

