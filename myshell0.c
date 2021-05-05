// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "util.h"
#include <termios.h>
#include <fcntl.h>
#define _XOPEN_SOURCE 800
#define error(a) \
   {             \
      perror(a); \
      exit(1);   \
   };
#define MAXLINE 200
#define MAXARGS 20

//extern void SetTermNoCanon(struct termios* saved_tm);
//extern void Berreskuratu_tm(struct termios* tm);


/////////// reading commands:

void (*oldHandler)();

int read_args(int* argcp, char* args[], int max, int* eofp)
{
	static char cmd[MAXLINE];
	char* cmdp;
	int ret, i;

	*argcp = 0;
	*eofp = 0;
	i = 0;
	while ((ret = read(0, cmd + i, 1)) == 1)
	{
		if (cmd[i] == '\n')
			break; // correct line
		i++;
		if (i >= MAXLINE)
		{
			ret = -2; // line too long
			break;
		}
	}
	switch (ret)
	{
	case 1:
		cmd[i + 1] = '\0'; // correct reading
		break;
	case 0:
		*eofp = 1; // end of file
		return 0;
		break;
	case -1:
		*argcp = -1; // reading failure
		fprintf(stderr, "Reading failure \n");
		return 0;
		break;
	case -2:
		*argcp = -1; // line too long
		fprintf(stderr, "Line too long -- removed command\n");
		return 0;
		break;
	}
	// Analyzing the line
	cmdp = cmd;
	for (i = 0; i < max; i++)
	{ /* to show every argument */
		if ((args[i] = strtok(cmdp, " \t\n")) == (char*)NULL)
			break;
		cmdp = NULL;
	}
	if (i >= max)
	{
		fprintf(stderr, "Too many arguments -- removed command\n");
		return 0;
	}
	*argcp = i;
	return 1;
}

///////////////////////////////////////

int execute(int argc, char* argv[])
{
	int child = fork();
	if (child == 0)
	{
		//signal(SIGINT, oldHandler);  //Restore oldHandler
		execvp(argv[0], argv);
		printf("Executed succesfuly");
		return 0;
	}
	else if (child == -1)
	{
		char* fork_error = "An error has occured";
		write(2, fork_error, sizeof(fork_error));
		return -1;
	}
	else
	{
		wait(NULL);
	}
}

void cd(char* dirname)
{
	if (chdir(dirname) != 0)
	{
		char* errormessage = "Directory not changed";
		write(2, errormessage, sizeof(errormessage));
	}
}

/*
int isPipe(char** args, char** parsedpipe, char** parsedpipe2, int* argc1, int* argc2)
{
	int i = 0;
	int found = 0;
	int k = 0;
	while (strcmp(args[i],"|") != 0 && found == 0 && args[i] != NULL) {
		parsedpipe[i] = args[i];
		if (strcmp(args[i], "|") == 0) {
			found = 1;
		}
		i++;
	}
	write(2, "abc", strlen("abc"));
	parsedpipe[i] = '\0';
	if (found) {
		int j = i + 1;
		while (args[j] != NULL) {
			parsedpipe2[k] = args[j];
			k++;
			j++;
		}
	}
	parsedpipe2[k] = '\0';
	*argc1 = i;
	*argc2 = k;
	return found;
}

int isPipe(char** args, char** parsedpipe, char** parsedpipe2, int* argc1, int* argc2)
{
	int i = 0;
	int found = 0;
	int k = 0;
	while (args[i] != '|' && found == 0 && args[i] != NULL) {
		parsedpipe[i] = args[i];
		if (args[i] == '|') {
			found = 1;
		}
		i++;
	}
	parsedpipe[i] = '\0';
	if (found) {
		int j = i + 1;
		while (args[j] != NULL) {
			parsedpipe2[k] = args[j];
			write(2, parsedpipe2[k], strlen(parsedpipe2[k]));
			k++;
			j++;
		}
	}
	parsedpipe2[k] = '\0';
	*argc1 = i;
	*argc2 = k;
	return found;
}
*/
int main()
{

	char* Prompt = "myShell0> ";
	int eof = 0;
	int argc;
	char* args[MAXARGS];
	//char* parsedPipe[MAXARGS];
	//char* parsedPipe2[MAXARGS];
	//int argcpipe1;
	//int argcpipe2;
	char yourPassword[3];
	char input;
	char hidePassword[1] = "*";
	struct termios saved_tm;
	int i = 0;


	//oldHandler = signal (SIGINT, SIG_IGN); /*Ignore Control+C */
	//int fd[2];
	//char* pipeChar[MAXARGS];
	//char* nopipe = "Nopipe";
	//char* yespipe = "YesPipe";


	while (1)
	{
		char* err = "1 \n";
		write(0, Prompt, strlen(Prompt));
		if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
		{

			if (!strcmp(args[0], "./cd"))
			{

				//write(2, yescd, sizeof(yescd));
				if (argc == 2)
				{
					cd(args[1]);
				}
				else
				{
					char* notcd = "Incorrect amount of arguments";
					write(2, notcd, sizeof(notcd));
				}
			}
			else
			{
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "Tools")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "WashingMachine")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "Document")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "GardenTools")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "SuspiciousShovel")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else if (!strcmp(args[0], "./cat") && !strcmp(args[1], "NeighboursBones")) {
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
							execute(argc, args[]);
						}
						else {
							write(2, "Try again. Type again the command, not only the password", strlen("Try again. Type again the command, not only the password"));
						}
						Berreskuratu_tm(&saved_tm);            // Terminalaren ezaugarriak berreskuratzen ditu
					}
					else {
						execute(argc, args[]);
					}
				}
				if (eof)
					exit(0);
			return 0;
		}
	}
}
