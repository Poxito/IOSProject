#include <termios.h>
#include <unistd.h>


void SetTermNoCanon( struct termios *SavedTM)
{
    struct termios tm;

    tcgetattr(0, &tm);			// uneko ezaugarriak irakurri
    tcgetattr(0, SavedTM);		// uneko ezaugarriak irakurri
    tm.c_lflag &= ~(ICANON|ECHO);	// sukaldatzea eta oihartzuna ezabatu
    tm.c_cc[VMIN]= 1;			
    tm.c_cc[VTIME]= 0;
    tcsetattr(0, TCSANOW, &tm);		// ezaugarriak aldatu

}
void Berreskuratu_tm(struct termios *tm)
{
    tcsetattr(0, TCSANOW, tm);
}


