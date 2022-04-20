/*
Realizzare un programma caratteristico della programmazione
concorrente quindi con lettori e scrittori con priorità agli scrittori
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define buff_maxSize 10 // rappresenta la risorsa condivisa su cui sincronizzare gli accessi, le scritture/letture

pthread_mutex_t mutex;								//mutex per la mutua esclusione
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;	//cond. var. per sospendere i lettori se non ci sono elementi da leggere -> buffer vuoto
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;	//cond. var. per sospendere i scrittori -> buffer pieno
int in  = 0;  										//indice del buffer in cui inserire/scrivere
int out = 0; 										//indice del buffer in cui prelevare/leggere
int buffer[buff_maxSize];
int nfull = 0;  									// numero di elementi presenti nel buffer
pthread_t scrittori[5],lettori[5];


void *producer(int p_name)
{
	int val_item;

	while(1) {
		val_item = rand() %100;
		pthread_mutex_lock(&mutex);					//scrittore chiede il mutex sulla risorsa condivisa; inizio sezione critica
		while (nfull == buff_maxSize)				// se il buffer è pieno
			pthread_cond_wait(&c_prod, &mutex); 	//scrittore in attesa se il buffer è pieno
		buffer[in] = val_item;						//elemento scritto nel buffer
		printf("[Scrittore] #%d: scritto il numero %d nella posizione #%d\n", p_name, buffer[in],in);
		fflush(stdout);
		in = (in+1)%buff_maxSize;			//posizione per la successiva scrittura del buffer circolare
		++ nfull;							//numero di elementi presenti nel buffer
		pthread_cond_signal(&c_cons);		//risveglio dei lettori che sono in wait
		pthread_mutex_unlock(&mutex);		//rilascio mutex; fine sezione critica
	}
}

void *consumer(int c_name )
{
	int val_item;
	while(1) {
		pthread_mutex_lock(&mutex);		 		 //lettore chiede il mutex sulla risorsa condivisa; inizio sezione critica
		while (nfull == 0)			     		 //se il buffer è vuoto
			pthread_cond_wait (&c_cons, &mutex); //lettore in attesa se il buffer è vuoto
		val_item = buffer[out];			     	 //elemento letto dal buffer
		printf("[Lettore] #%d: letto numero %d nella posizione #%d\n", c_name, val_item, out);
		fflush(stdout);
		out = (out+1)%buff_maxSize;		 		//posizione per la successiva lettura del buffer circolare
		-- nfull;				 				//numero di elementi presenti nel buffer
		pthread_cond_signal(&c_prod);		 	//risveglio dei scrittori che sono in wait
		pthread_mutex_unlock(&mutex);		 	//rilascio mutex; fine sezione critica
	}
}


int main()
{

	pthread_mutex_init(&mutex, NULL);

	int names[5] = {1,2,3,4,5}; // per individuare i singoli scrittori/lettori

	for(int i = 0; i < 5; i++) {
		pthread_create(&scrittori[i], NULL, (void *)producer, (void *)names[i]);
	}
	for(int i = 0; i < 5; i++) {
		pthread_create(&lettori[i], NULL, (void *)consumer, (void *)names[i]);
	}

	sleep (1);  //giusto per scrivere e leggere un pò
	for(int i = 0; i < 5; i++) {
		pthread_kill(&scrittori[i], (void *)NULL);
		pthread_kill(&scrittori[i], (void *)NULL);
	}

}

