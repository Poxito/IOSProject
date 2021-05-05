#include <stdio.h>
#include <unistd.h> /*for STDOUT_FILENO*/
#include <stdlib.h>
#include <fcntl.h> /*for open*/
#include <string.h>

int main(int argc,char *argv[])
{
        int fd, i, buf;	
        if(argc == 1)
        {
            while(1){
                read(0,&buf,1);
                write(1,&buf,1);
            }
        }
        else if(argc > 1)
        {
                for (i = 1; i < argc; i++) {                    /*iterate the loop for total argument count.*/

                        fd = open(argv[1],O_RDONLY);            /*open the file in READONLY mode*/

                        if(fd < 0) {
                                perror("open");
                                goto OUT;
                        }

                        while(read(fd,&buf,1))                   /*Read one byte at a time*/

                                write(1,&buf,1);     /*Write the byte on Stdout*/

                        close(fd);                              /*close the file discriptor*/
                }
        }
	else{
             	write(2, "Error. Type the command correctly. If you don't know how the command is use the man page. \n", strlen("Error. Type the command correctly. If you don't know how the command is use the man page.  \n"));
        }

	return 0;
OUT:
    	return -1;
}
