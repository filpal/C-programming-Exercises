/*
 ============================================================================
Scrivere un programma C che prenda come parametro due nomi di file inputFile ed outputFile
(controllare che il numero di argomenti passati sia corretto) il programma dovrà generare un
processo figlio, PF che aprirà il file inputFile copiando i primi 40
caratteri di inputFile in outputFile aggiungendo alla fine il proprio PID. Il padre attenderà
il figlio ed aggiungerà ad outputF il proprio PID
 ============================================================================
 */

#include <stdio.h> /* perror */
#include <unistd.h> /* write, lseek, close */
#include <stdlib.h> /*exit*/
#include <string.h> /*strcat*/
#include <sys/wait.h>


int main(int argc, char **argv)
{
	FILE * infile;
	FILE * oufile;
	int pid;
	char buf_in[200];
	char buf_out[200];

	if (argc != 3)
	{
		printf(" uso: nomeprogramma <inputFile> <outputFile> \n");
		exit (1);
	}

	if ((pid = fork()) == -1)	/*Esecuzione fork*/
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0) 			/*Processo figlio*/

	{ 							/* Apertura file inputFile*/
		infile=fopen(argv[1], "r");
								/*legge i primi 40 caratteri*/

		while(fscanf(infile, "%s", buf_in)!=EOF)
		{
			strcat(buf_out, buf_in);
			strcat(buf_out, " "); //aggiungo lo spazio tra le parole
		}

		fclose(infile); 		/*chiude il proprio file descriptor*/

		oufile=fopen(argv[2], "a+");

		fprintf(oufile,"%s\n", buf_out);

		fprintf(oufile, "(PID:%d) PF \n", getpid());

		fclose(oufile); 		/*chiude il proprio file descriptor*/

	}

	else  //padre
	{
		waitpid(pid,NULL,0);

		if ((oufile=fopen(argv[2], "a+")) == NULL)
		{
			printf("Errore apertura inputFile da leggere %s\n:",argv[1]);
			exit(1);
		}

		fprintf(oufile, "(PID:%d) PP \n", getpid());

		fclose(oufile); 		/* chiude il proprio file descriptor */

		return 0;

	}

}



