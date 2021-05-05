#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    if (argc < 3){
        write(2, "Too few arguments", strlen("Too few arguments"));
        return -1;
    }

    files[0] = open(argv[1], O_RDONLY);
    if (files[0] == -1){/* Check if file opened */
        write(2, "Couldn't open the file", strlen("Couldn't open the file"));
        return -1;
    } 
        
    files[1] = open(argv[2], O_WRONLY | O_CREAT);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        write(2, "Couldn't open the file", strlen("Couldn't open the file"));
        close(files[0]);
        return -1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

    return 0;
}
