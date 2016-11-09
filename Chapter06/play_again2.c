/* play_again0.c
 * purpose : ask if user wants another transaction
 * method : set tty into char-by-char mode and no echo mode,read char,return result
 * return : 0=>yes,1=>no
 * better: timeout if user walks away
 */

#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"
int get_response( char * );
void set_cr_noecho_mode();
void tty_mode(int);
int main()
{
	int response ;
	tty_mode(0);	//save tty mode
	set_cr_noecho_mode();
	response = get_response(QUESTION);
	tty_mode(1);	//restore tty mode
	printf("response = %d \n",response);
	return response;
}


int get_response(char * question)
{
	int input;
	printf("%s(y/n)?",question);
	while(1){
		switch(input = getchar()){
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
		}
	}
}
void set_cr_noecho_mode()
{
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&ttystate);
}
void tty_mode(int how)
{
	static struct termios original_mode;
	if (how == 0)
	{
		tcgetattr(0,&original_mode);
	}
	else{
		tcsetattr(0,TCSANOW,&original_mode);
	}
}