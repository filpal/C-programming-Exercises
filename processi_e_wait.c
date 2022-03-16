#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
	int pid, pidw, status, i, n;
	if(argc == 2)
		n = atoi(argv[1]);
	else
		n = 10; /* valore di default */
	/* genero n figli */
	for(i=0;i<n;i++)
	{
		pid = fork();

		if( pid )
		{
			/* siamo nel padre */
			printf("Processo padre(pid=%d): i=%d, processo figlio (pid=%d)\n",
					getpid(),i, pid);
		}
		else {
			/* siamo nel figlio */
			printf("Processo figlio(pid=%d): generato dal proc. (pid=%d) con i=%d\n",
					getpid(),getppid(),i);
			sleep(5+i);
			exit(i);
		}
	}
	/* aspetto la terminazione di uno qualsiasi */
	//pidw = wait(&status);
	/* aspetto la terminazione di tutti */
	for(int i=0; i< n; ++i)
			wait(&status);
	if(WIFEXITED(status))
		printf("Processo %d terminato con exit(%d)\n",
				pidw,WEXITSTATUS(status));
	else
		printf("Processo %d terminato con segnale.\n",
				pidw);
	return(0);
}