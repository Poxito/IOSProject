// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
//#include "util.h"
#include <termios.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20

extern void SetTermNoCanon( struct termios *SavedTM);
extern void Berreskuratu_tm(struct termios *tm);


/////////// reading commands:

void(*oldHandler)();

int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;
   i=0;
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;
      if (i>=MAXLINE) {
         ret=-2;        // line too long
         break;
      }
   }
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
              break;
     case 0 : *eofp = 1;        // end of file
              return 0;
              break;
     case -1 : *argcp = -1;     // reading failure
              fprintf(stderr,"Reading failure \n");
              return 0;
              break;
     case -2 : *argcp = -1;     // line too long
              fprintf(stderr,"Line too long -- removed command\n");
              return 0;
              break;
   }
   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }
   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   *argcp= i;
   return 1;
}

///////////////////////////////////////

int execute(int argc, char *argv[])
{
	char path[100] = "/users/alumnos/acaf/acaf0234/root/";
	int child =fork();
	if(child == 0){
		//signal(SIGINT, oldHandler);  //Restore oldHandler
		strcat(path, argv[0]);
       		execvp(path, argv);
		printf("Executed succesfuly");
		return 0;
	}else if(child == -1){
		char * fork_error = "An error has occured";
		write(2, fork_error, sizeof(fork_error));
		return -1;
	}else{
		wait(NULL);
	}
}

void cd(char * dirname)
{
	if(chdir(dirname) != 0){
		char * errormessage = "Directory not changed";
		write(2, errormessage, sizeof(errormessage)); 
	}
}
/*
int passwordComputer(){
	
	char password[3];
	int x = 10;

	while(x!=0){
		printf("\n Enter the password");
		scanf("%s", *password);

		if(password=="tbl"){
			execvp....
			x = 0;
		}else{
			printf("Wrong password, try again");
		}
		printf("\n");
	}
	return 0;
}*/


int main ()
{
   
   char * Prompt = "myShell0> ";
   int eof= 0;
   int argc;
   char *args[MAXARGS];
   char *yourPassword[6];
   int computerFD;
   char *buffer;
   char hidePassword[1] = "*";
   char input;
   struct termios saved_tm;
   int i = 0;


   //oldHandler = signal (SIGINT, SIG_IGN); /*Ignore Control+C */

    while (1) {
        write(0,Prompt, strlen(Prompt));
        if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
            if(!strcmp(args[0],"cd")){
		        if(argc == 2){
			        cd(args[1]);
		        }else{
			        char * notcd = "Incorrect amount of arguments\n";
			        write(2, notcd, sizeof(notcd)); 
		        }
	        }else{
		        if (!strcmp(args[0], "./cat") && !strcmp(args[1], "Computer")) {
			        printf("Enter the password\n");
			        SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

			        while (i < 3) {
				        read(0, &input, 1);
				        yourPassword[i] = input;
				        write(1, hidePassword, sizeof(hidePassword));
				        i++;
			        }
			        write(1, "\n", strlen("\n"));

			        if (!strcmp(yourPassword, "tbl")) {
				        execute(argc, args);
                        /*
                        for(int j = 0; j < sizeof(yourPassword); j++){
                             yourPassword[j] = null;
                        }*/
                        i = 0;
			        }else {
				        write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
			        }
			        Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
			    }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "Tools")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

				    while (i < 4) {
			    	    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

				    if (!strcmp(yourPassword, "base")) {
					    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					
                }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "WashingMachine")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

				    while (i < 4) {
					    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

			        if (!strcmp(yourPassword, "base")) {
					    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu

			    }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "Document")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

				    while (i < 4) {
					    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

				    if (!strcmp(yourPassword, "base")) {
					    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu

		        }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "GardenTools")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

				    while (i < 3) {
					    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

				    if (!strcmp(yourPassword, "key")) {
					    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu

			    }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "SuspiciousShovel")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

				    while (i < 3) {
					    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

				    if (!strcmp(yourPassword, "key")) {
			    	    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
			
                }else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "NeighboursBones")) {
				    printf("Enter the password\n");
				    SetTermNoCanon(&saved_tm);		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

			        while (i < 6) {
					    read(0, &input, 1);
					    yourPassword[i] = input;
					    write(1, hidePassword, sizeof(hidePassword));
					    i++;
				    }
				    write(1, "\n", strlen("\n"));

				    if (!strcmp(yourPassword, "shovel")) {
					    execute(argc, args);
                        i = 0;
				    }else {
					    write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
				    }
				    Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
		        }else {
			    	execute(argc, args);
			    }
	        } 
        }
    }
    if (eof) exit(0);
	return 0;
}
