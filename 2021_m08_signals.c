/*============================================================================
Si vuole realizzare un programma C che, utilizzando le system call di UNIX,
realizzi uno schema di comunicazione tra due processi (padre e figlio) mediante
l’accesso ad un file condiviso. In particolare, tenere conto delle seguenti specifiche:
a. il figlio riveste il ruolo di mittente dei messaggi;
b. il padre è il destinatario;
c. assumere un numero prefissato di messaggi (ad esempio, 20) a lunghezza fissa (ad esempio, 8 bytes).
============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h> /* uso i segnali*/
#include <fcntl.h> /* uso i file*/
#include <string.h> /* per manipolare i messaggi*/
#include <unistd.h>
#include <linux/stat.h>
#define max 20 /* numero di messaggi */

int fd;
int pid, ppid;
int cont=0;
/* prototipi handlers: */
void send(int signo);
void receive(int signo);
void fine(int signo);

int main()
{
	fd=creat("mailbox.tmp", 0777); /* creazione file temporaneo */
	close(fd);
	fd=open("mailbox.tmp",O_RDWR); /*apertura file */

	pid=fork(); /*il figlio eredita fd: I/O pointer condiviso*/
	if (pid==0) /*codice figlio: mittente*/
	{
		ppid=getppid();
		signal(SIGUSR1, send); /* SIGUSR1: invio di un nuovo messaggio */
		signal(SIGUSR2, fine); /* SIGUSR2: fine della comunicazione */
		sleep(1); /*per evitare problemi di sincronizzazione */
		send(-1); /* il figlio prende l’iniziativa:
		primo messaggio */
		while(1) pause(); /*ciclo di attesa*/
	}
	else if (pid>0) /* codice padre */
	{
		signal(SIGUSR1, receive); /*SIGUSR1: ricezione di un nuovo messaggio */
		while(1) pause(); /*ciclo di attesa del padre*/
	}
}
/* fine main */

void send(int signo) /* interfaccia fissa: handler!*/
{
	char buff[80]="Inizio!\n";
	cont++;
	lseek(fd,0,0); /*reset dell’I/O pointer*/
	if (signo==-1) /* normale chiamata di procedura*/
		printf("%s",buff); /*stampa*/
	sprintf(buff, "Ciao babbo %2d\n",cont );
	write(fd, buff,15 ); /* scrittura nel file */
	kill(ppid, SIGUSR1); /* risveglio del padre*/
return;
}
void receive(int signo)
{
	char buff[80];
	int status;
	cont++;
	lseek(fd, 0,0); /* reset dell’I/O pointer */
	read(fd, buff, 15); /* lettura dal file */
	write(1, buff, 15); /* stampa su stdout il msg.*/
	if (cont < max)
		kill(pid,SIGUSR1); /* ancora messaggi*/
	else
	{
		close(fd); /*chiusura file*/
		kill(pid, SIGUSR2); /* ultimo messaggio*/
		wait(&status);
		printf("stato figlio:%d\n", status);
		exit(0);
	}
	return;
}

void fine(int signo) /* terminazione del figlio */
{
	char buff[25]= "FINE\n";
	close(fd); /* chiusura file*/
	printf("%s",buff); /* stampa */
	//unlink("mailbox.tmp"); /* cancellazione file */
	exit(0);
}







