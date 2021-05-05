#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_SIZE 24

extern void SetTermNoCanon(struct termios *SavedTM);
extern void Berreskuratu_tm(struct termios *tm);
extern int one_page(FILE* fd, int max);



int one_page(FILE* fd, int max)
{
   int c;
   int n= 0;

	while ((c=getc(fd)) != EOF) {
		putc(c, stdout);
		if (c == '\n') n++;
		if (n >= max) break;
	}
	return(n);
}

int gehio(int argkop, char *arg[]) 
{
	int lerroak= PAGE_SIZE;
        char buf[80];
	char c;
	int r;
	FILE* fp;

	struct termios saved_tm;

	if ((fp=fopen(arg[1], "r")) == NULL) {
        	strcpy (buf, "Errorea fitxategia irekitzean \n");
        	write(2, buf, strlen(buf));
   		return -1;
		}


	SetTermNoCanon( &saved_tm );	// Terminalaren ezaugarriak aldatzen ditu, jatorrizkoak gordez

	while (one_page(fp, lerroak)) {
		if ((r=read(0, &c, 1)) == -1) {
			perror("akats desegokia");
			Berreskuratu_tm(&saved_tm);
			fclose(fp);
			exit(1);
		}
		else if (r == 0) lerroak= PAGE_SIZE;
		else switch (c) {
			case 'q': Berreskuratu_tm(&saved_tm);
				  fclose(fp);
			          return 0;
			case ' ': lerroak= PAGE_SIZE;
			          break;
			default:  lerroak= 1;
		}
	}
	Berreskuratu_tm(&saved_tm);
	fclose(fp);
	return 0;
}

