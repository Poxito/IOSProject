#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *src = argv[1];
    	char *dest = argv[2];
	char newplace[50];

	if(argc < 3){
		fprintf(stderr, "usage: %s src dest\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(argc == 3){
		DIR *cwd;
		cwd = opendir(dest);

		if(cwd == NULL){
			if(rename(src,dest) != 0)
				write(2, "Error: File not moved\n", strlen("Error: File not moved\n"));
			else
				write(1, "File renamed correctly\n", strlen("File renamed correctly\n"));		

		}else{
			char *path;
			path = getcwd(newplace, 50);  //get current working directory
			strcat(newplace, "/");
			strcat(newplace, dest);   //attach mv location to path 
			strcat(newplace, "/");
			strcat(newplace, src);       //keep original file name
			if(rename(src,path) != 1)
				write(1, "Success\n", strlen("Success\n"));
			else
				write(2, "Error: Directory not found un CWD\n", strlen("Error: Directory not found in CWD\n"));
			closedir(cwd);

		}
	}
}
