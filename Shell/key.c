//

#include <stdio.h>

int main()
{
	int c,n = 0;

	while (( c=getchar()) != 'Q') {
		if (c == '\033') {
			//these two strange prints are from:
			//https://itnext.io/overwrite-previously-printed-lines-4218a9563527
			//and they delete the previous line
			printf("\033[1A");//line up
			printf("\x1b[2K");//delete line
			// printf("%c\n", (char)c);
			printf("got an arrow ");
			getchar(); //skip the [
			switch(getchar()) { // the real value
			case 'A':
			    // code for arrow up
			    printf("up\n");
			    break;
			case 'B':
			    // code for arrow down
			    printf("down\n");
			    break;
		}
		else
		{
			printf("char %3d is %c code %d\n", n++,c,c);
		}
	}

	return 0;
}

//to get more info , you can read teh book chapter 5,page 151 (172 in pdf)
//also take a look here: https://dev.to/napicella/linux-terminals-tty-pty-and-shell-192e

// #include <stdio.h>
// #include <stdlib.h>
// #include <termios.h>

// int main() {
//     struct termios term, term_orig;
//     tcgetattr(STDIN_FILENO, &term);
//     term_orig = term;
//     term.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);

//     int c, n = 0;
//     while ((c = getchar()) != EOF && c != 'Q') {
//         if (c == '\033') {
//             // code to process arrow keys
//             // ...
//         } else {
//             printf("char %3d is %c code %d\n", n++, c, c);
//         }
//     }

//     tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
//     return 0;
// }
