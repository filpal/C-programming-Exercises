/*
 ============================================================================
Alla stazione di una funivia, che può trasportare al massimo 20 persone,
ci sono due porte di accesso. Si ipotizza un flusso continuo di
viaggiatori. Dopo l'arrivo del 20-esimo passeggero le porte si chiudono e
la funivia parte. Implementare il comportamento delle porte.
 ============================================================================
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for sleeep


int contapersone = 0;
int porteaperte = 1;  //flag che indica porta aperta o chiusa,

pthread_mutex_t m;


int * salipersoneporta (void * i) {

	while (1)
	{
	  pthread_mutex_lock(&m);

	  if (contapersone < 20)
	  {
		contapersone++;
		printf("[ %s ]: persone presenti %d\n",  (char*)i, contapersone); fflush(stdout);
		pthread_mutex_unlock(&m);
		sleep(2);
	  }
	  else	if (contapersone == 20)
		{
			porteaperte = 0;
			printf("[ %s] persone presenti %d, capienza raggiunta\n", (char*)i, contapersone); fflush(stdout);
			pthread_mutex_unlock(&m);
			return 0;
		}
		else
		{
			printf("[ %ld ] capienza superata %d, non faccio nulla sto uscendo\n", pthread_self(), contapersone); fflush(stdout);
			pthread_mutex_unlock(&m);
			return 0;
		}

	}
}


int main(void) {

	pthread_t porta1, porta2;

	pthread_create(&porta1,NULL,(void *)salipersoneporta,(void *)"porta1");

	pthread_create(&porta2,NULL,(void *)salipersoneporta,(void *)"porta2");


	if(
			( pthread_join(porta1,NULL) && pthread_join(porta2,NULL) )==0
	){
	printf("funivia piena... funivia parte!\n");
	}
	return 0;
}
