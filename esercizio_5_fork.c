/*
 ============================================================================
Creare un programma che crea un processo figlio tramite fork e questo processo
va a duplicare le variabili del processo genitore e poi il figlio invece andrà
a creare un nuovo thread che incrementa le variabili
 ============================================================================
 */

/* interfaccia per fork() */
#include <sys/types.h>
#include <unistd.h>
/* interfaccia per printf() */
#include <stdio.h>

static int var_A, var_B;

int main(int argc, char **argv) {
	int var_a;
	var_A = 10;
	var_B = 20;
	switch(fork()) {
	case 0: 						/* figlio */
		printf("[F]: accedo a var_B:%d e var_A:%d\n", var_B, var_A);
		var_B = 11;
		printf("[F]: var_B ora vale: %d\n",var_B);
		var_a++;
		printf("[F]: var_A ora vale: %d\n",var_A);
		int pfd[2];
		int nread, k= 100;
		if (pipe(pfd) == -1) {
				perror("pipe() fallita)");
				exit(-1);
			}

		switch(fork()) {
			case 0: 				/* nipote*/
					k++;
					close(pfd[0]);
					write(pfd[1], &k, sizeof (int));
					printf("[N]: var incrementata dal nipote: %d\n", k);

					break;
			case -1:				/* fork error */
					break;
			default:				/* figlio*/
				close(pfd[1]);
				read(pfd[0], &k, sizeof (int));
				printf("[F]: var incrementata dal nipote: %d\n", k);
				break;
		}
	case -1: 						/* fork error */
		break;
	default: 						/* padre */
		printf("[P]: accedo a var_B:%d e var_A:%d\n", var_B, var_A);
		var_B = 15;
		printf("[P]: var_B ora vale: %d\n",var_B);
		var_A--;
		printf("[P]: var_A ora vale: %d\n",var_A);
	}
	return(0);
}