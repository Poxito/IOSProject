#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARG 6
#define MAX_CAR 25
#define MAXLINE 250

extern void SetTermNoCanon( struct termios *SavedTM);
extern void Berreskuratu_tm(struct termios *tm);
extern int gehio(int n, char *par);

int argumentuak_sortu(char *lerroa, int *zenb, char *zerrenda[])
{
   char* cmdp;
   int i;

   cmdp= lerroa;
   for (i=0; i<MAX_ARG; i++) {  		// argumentu bakoitza erakusteko
      if ((zerrenda[i]= strtok(cmdp, " ")) == (char*)NULL) break;
      cmdp= NULL;
   }

   if (i >= MAX_ARG) {
      fprintf(stderr, "Argumentu gehiegi -- baztertutako komandoa\n");
      return 0;
   }
   *zenb= i;
   return 1;
}

int main (int argc, char* argv[]) 
{
	char c;
	char lerroa[MAXLINE];
	char param[MAXLINE];
	int zenb;
	char zerrenda[MAX_ARG][MAX_CAR];
	int r;
//	FILE* fp;
	struct termios SavedTM;

	if (argc != 1) {
		printf("Erabilera: ./toolbox \n");
		exit(1);
	}

	while (1) {
		printf("\n              M E N U A \n");
		printf("            ------- \n");
		printf("Sartu ondorengo aukeretako bat: \n\n");
		printf("   g  Fitxategi baten edukia erakusten du \n\n");
		printf("   k  Fitxategi bat beste batean kopiatzen du \n\n");
		printf("   e  Fitxategiak ezabatu \n\n");
		printf("   ... \n\n");
		printf("   q irteteko \n");
		

		SetTermNoCanon( &SavedTM );		// Terminalaren ezaugarriak aldatzen ditu jatorrizkoak gordez

		if ((r=read(0, &c, 1)) == -1) {
			perror("error fatal");			
			Berreskuratu_tm(&SavedTM);	// Terminalaren ezaugarriak berreskuratzen ditu
			exit(1);
		}
		Berreskuratu_tm(&SavedTM);		// Terminalaren ezaugarriak berreskuratzen ditu

		switch (c) {
			case 'q': exit(0);
			case 'g': 
				printf("Fitxategiaren izena: ");
				scanf("%s", param);
				strcpy(lerroa, "mas ");
				strcat(lerroa, param);
				if (argumentuak_sortu(lerroa,&zenb,&zerrenda)==0){
				fprintf(stderr, "Argumentu gehiegi -- baztertutako komandoa\n");
      				break;
   				}
				if (gehio(zenb,zerrenda) < 0) printf("Ezin izan dut gehio exekutatu\n");
			        break;
			default: ;
		}
	}

	exit(0);
}

