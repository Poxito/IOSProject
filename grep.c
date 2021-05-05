#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, const char *argv[])
{       
	int fd,r,j;
	char buff,line[1000];
	if (argc < 3|| argc > 3){
        	write(2, "Invalid arguments. \n", strlen("Invalid arguments. \n"));
        	return -1;
   	 }

	if((fd=open(argv[2],O_RDONLY)) != -1){
    		while((r=read(fd,&buff,sizeof(char)))!=0){
        		if(buff != '\n'){
            			line[j]=buff;
            			j++;
        		}
        		else{
            			line[j]='\0';
            			if(strstr(line,argv[1]))
                		printf("%s\n",line);
            			memset(line,0,sizeof(line));
            			j=0;
        		}
    		}
	}else{
    		write(2, "Cannot open specified file. \n", strlen("Cannot open the specified file.\n"));
    	return -1;
	}
}
           

