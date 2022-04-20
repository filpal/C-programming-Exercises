/*
 Si vuole realizzare un sistema per la gestione delle transazioni commerciali relative ad un
 mercato ortofrutticolo all’ingrosso; il sistema deve permettere ad un numero arbitrario di thread concorrenti,
 ciascuno rappresentante un utente, di effettuare acquisti (nel caso di grossisti) e vendite (nel caso di produttori).
 Per semplicità si supponga che il mercato ha una capacità massima M che esprime il numero massimo di quintali di
 merce che possono essere immagazzinati; gli utenti sono di due tipi: produttore e grossista.
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


#define MercatoSize 5 // assumiamo che il mercato ha una capienza max di 5 "lotti" di frutta, ogni lotto max 100 tonnellate di frutta

sem_t empty;				//semaforo per sospendere i grossisti se non ci sono lotti di frutta da acquistare
sem_t full;				//semaforo per sospendere i produttori se tutti i lotti di frutta sono pieni
int in = 0;  				//indice per inserire la merce nel mercato: frutta prodotta messa in vendita dal produttore
int out = 0; 				//indice per togliere la merce dal mercato: frutta acquistata dal grossista
int bufferMercato[MercatoSize];
pthread_mutex_t mutex;

void *producer(int p_name)
{
    int ton_frutta;
    while(1) {
    	ton_frutta = rand() %100; 		// Produce un numero random ton di frutta, max 100
        sem_wait(&empty);    			// controlla il semaforo se ci sono "lotti" vuoti;
        					// se non c'è spazio per inserire si ferma, se c'è spazio decrementa
        					// le posizioni libere del buffer
        pthread_mutex_lock(&mutex); 		// chiede il mutex sulla risorsa condivisa; inizio sezione critica
        bufferMercato[in] = ton_frutta;    	// inserisce nel mercato la frutta prodotta
        printf("[Produttore] #%d: in vendita %d tonnellate di frutta nel lotto #%d\n", p_name, bufferMercato[in],in);
        in = (in+1)%MercatoSize;		//posiziona l'indice nella successiva posizione del buffer
        pthread_mutex_unlock(&mutex);		//rilascio mutex; fine sezione critica
        sem_post(&full);			//incrementa il semaforo full, dato che ha riempito in bufferMercato[in]
    }
}
void *consumer(int c_name )
{
    while(1) {
        sem_wait(&full);			// controlla il semaforo se ci sono "posizioni" piene da cui acquistare;
        					// se il mercato è vuoto si blocca
        pthread_mutex_lock(&mutex);		// chiede il mutex sulla risorsa condivisa; inizio sezione critica
        int item = bufferMercato[out];		// acquista dal mercato la frutta in posozione out
        printf("[Grossista] #%d: acquistate %d tonnellate di frutta, lotto #%d\n", c_name, item, out);
        out = (out+1)%MercatoSize;		// posiione l'indice nella successiva posizione del buffer
        pthread_mutex_unlock(&mutex);		// rilascio mutex; fine sezione critica
        sem_post(&empty);			// incrementa il semaforo empy, data che a svuotato bufferMercato[out]
    }
}

int main()
{

    pthread_t produttori[5],consumatori[5];  //ipotizziamo 5 produttori, 5 consumatori
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,MercatoSize);
    sem_init(&full,0,0);

    int names[5] = {1,2,3,4,5}; // per individuare i singoli produttori/consumatori

    for(int i = 0; i < 5; i++) {
        pthread_create(&produttori[i], NULL, (void *)producer, names[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&consumatori[i], NULL, (void *)consumer, names[i]);
    }

    
}
