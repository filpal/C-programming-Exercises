/*
 ============================================================================
Si scriva un programma in C che, utilizzando le system call di UNIX, dovr� funzionare nel modo seguente:
a. il processo �padre� P0 deve creare 2 processi figli (P1 e P2),
	il figlio P1 deve aspettare N1 secondi e successivamente eseguire il comando C;
b. il figlio P2 dopo N2 secondi dalla sua creazione dovr� provocare la terminazione del processo fratello
	P1 e successivamente terminare, nel frattempo P2 deve periodicamente sincronizzarsi con il padre P0
	(si assuma la frequenza di 1 segnale al secondo);
c. il padre P0, dopo aver creato i figli, si pone in attesa di segnali da P1. Per ogni segnale ricevuto,
	dovr� stampare il proprio PID: al n-mo segnale ricevuto dovr� attendere la terminazione dei figli e
	successivamente terminare.
 ============================================================================
 */

// esempio di esecuzione: ./nome_programma 3 1 5 ls -la  ./nome_programma 3 9 5 ls -la

#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

int PID1, PID2, N;
int cont=0; 					/* contatore dei segnali ricevuti da P0 */
void gestore_P(int sig); 		/* gestore di SIGUSR1 per P0 */
void timeout(int sig); 			/* gestore timeout P2 */

main(int argc , char *argv[])
{
 int N1, N2, pf, status, i;
 char com[20];

 if (argc!=5)
  { printf("sintassi sbagliata!\n");
  	  exit(1);
  }

  N = atoi(argv[1]);
  N1 = atoi(argv[2]);
  N2 = atoi(argv[3]);
  strcpy(com, argv[4]);

  if ((PID1=fork())==0)
  {									/* codice figlio P1 */
	  printf("[F1] %d: sto andando in sleep\n", getpid());  fflush(stdout);
	  sleep(N1);					/* sleep N1 secondi */
	  printf("[F1] %d: terminato sleep di %d, eseguo comando\n",getpid(), N1); fflush(stdout);
	  //execlp(com,com,(char *)0);	/* esegue comando   */
	  execvp (com, com);			/* esegue comando   */
	  //exit(0);					/* termina          */
	  printf("[F1] %d: sto andando di nuovo in sleep\n", getpid());  fflush(stdout);
	  sleep(100);
   }
   else if (PID1<0)
	   exit(-1);

   if ((PID2=fork())==0)
   {								/* codice figlio P2 */
	   int pp=getppid();
	   signal(SIGALRM, timeout);	/* installazione signal: esecuzione della funzione timeout se arriva la signal alarm */
	   alarm(N2);					/*imposta alarm dopo N2 secondi */
	   for(;;)
	   {							/* in un for infinito*/
		   sleep(1);				/* sleep 1 secondo */
		   kill(pp, SIGUSR1);		/* invia la signal SIGUSR1 al padre*/
	   }
	   exit(0);
   }
   else if (PID2<0)
	   exit(-1);
   /* padre */
   signal(SIGUSR1, gestore_P);		/*installa la signal: se riceve la signal SIGUSR1 esegue la funzione gestore_P*/
   while(1) pause();


   exit(0);
}


void gestore_P(int sig)
{
	int i, status, pf;
    cont++;
    printf("[P] %d: ricevuto %d (cont=%d)! \n", getpid(), sig, cont); fflush(stdout);
    if (cont==N)
    {
    	for (i=0; i<2; i++)
    	{
    		pf=wait(&status);
    		if ((char)status==0)
    			{
    			printf("terminato processo %d con stato %d\n", pf, (char)status);
    			fflush(stdout);
    			}
    		else
    			{
    			printf("terminato processo %d inviato segnale %d\n", pf, (char)status);
    			fflush(stdout);
    			}
    	}
    	printf("[P] terminato processo %d \n", getpid());
    	exit(0);
   }
    return;
}

void timeout(int sig)
{
	printf("[F2] %d: scaduto timeout!\n", getpid());
    kill(PID1, SIGKILL);
    exit(0);
}




