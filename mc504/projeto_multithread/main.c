#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "immigrants.h"
#include "judge.h"
#include "spectators.h"

#define N_IMG 10
#define N_SPEC 10
#define N_JDG 1
#define N_ATND 10
#define HALL_FULL 10

/* capacidade maxima do hall de entrada */
/* acho que podemos usar o proprio semaforo para controlar 
 o numero de immigrantes que entraram */
sem_t hall_cap;

/* controla entrada e saida de imigrantes */
pthread_mutex_t door_in, door_out;

/* caixas disponiveis para realizacao do CheckIn */
sem_t attendant;

/* numero de imigrantes que fizeram check in */
volatile int checkedIn;

int main() {
    pthread_t thr_img[N_IMG], thr_spec[N_SPEC], thr_jdg[N_JDG];
    int i, hall_full, n_atnd;
    
    hall_full = HALL_FULL;
    n_atnd = N_ATND;
    
    sem_init (&hall_cap, 0, hall_full);
    sem_init (&attendant, 0, n_atnd);
    
    for (i = 0; i < N_IMG; i++)
        pthread_create(&thr_img[i], NULL, f_img, NULL);
    
    for (i = 0; i < N_SPEC; i++)
        pthread_create(&thr_spec[i], NULL, f_spec, NULL);
    
    for (i = 0; i < N_JDG; i++)
        pthread_create(&thr_jdg[i], NULL, f_jdg, NULL);
    
    
    for (i = 0; i < N_IMG; i++)
        pthread_join(thr_img[i], NULL);
    
    for (i = 0; i < N_SPEC; i++)
        pthread_join(thr_spec[i], NULL);
    
    for (i = 0; i < N_JDG; i++)
        pthread_join(thr_jdg[i], NULL);
    
    sem_destroy (&hall_cap);
    sem_destroy(&attendant);
    pthread_mutex_destroy(&door_in);
    pthread_mutex_destroy(&door_out);
    
    return 0;
}
