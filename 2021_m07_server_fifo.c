/*
 ============================================================================
Si vuole realizzare un’applicazione in ambiente UNIX basata su uno schema client-server.
L’applicazione deve essere costituita da due processi (client e server, non necessariamente parenti):
 a. il client è un programma che prevede una sintassi di invocazione del tipo <client com fileout>.
 	 Il client interagisce con il server per richiedere l’esecuzione di un servizio
 	 (l’esecuzione del comando com) con ridirezione sul file fileout;
 b. il server è un programma (che non prevede argomenti) che, una volta ricevuti dal client com e fileout,
 	 provvede all’esecuzione di com con ridirezione su fileout.
 ============================================================================
 */

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <sys/wait.h>

#define size 16


int main()
{
	int fdin;
	int pid, stato;
	char msg[size], fileout[size];

	//umask(0);
	//mknod("server.in", S_IFIFO|0666,0);

	if((fdin=mkfifo("server.in", 0777))<0)

		perror("error server mkfifo"); /*la fifo esiste già*/

	if ( (fdin = open("server.in", O_RDONLY) ) < 0 )
	{
		perror("server_open in:");
		exit(-1);
	}
	read(fdin,msg,size); /*lettura pipe FIFO */
	close(fdin);

	printf("Il comando da eseguire: %s\n",msg);
	printf("File out: %s\n",fileout);
	pid=fork();

	if (!pid)
	{
		close(1);
		fdin=creat(&msg[1], 0777); /* rid. output */

		execlp(&msg[0], &msg[0], (char *)0);
		perror("execlp");
		exit(-1);
	}
	else
	{
		wait(&stato);
		printf("stato figlio %d\n", stato>>8);
		exit(0);
	}
}