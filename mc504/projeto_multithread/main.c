#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "immigrants.h"
#include "judge.h"
#include "spectators.h"

int main() {
    pthread_t thr_img[N_IMG], thr_spec[N_SPEC], thr_jdg[N_JDG];
    int i, hall_full, n_atnd;
    
    int imgID[N_IMG], specID[N_SPEC];
    
    hall_full = HALL_FULL;
    n_atnd = N_ATND;
    
    pthread_mutex_init (&door, NULL);
    pthread_cond_init (&nojudge, NULL);
    
    sem_init (&hall_cap, 0, hall_full);
    pthread_mutex_init (&attendant, NULL);
    
    for (i = 0; i < N_IMG; i++)
        pthread_create(&thr_img[i], NULL, f_img, (void*) &imgID);
    
    for (i = 0; i < N_SPEC; i++)
        pthread_create(&thr_spec[i], NULL, f_spec, (void*) &specID);
    
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
    pthread_mutex_destroy(&door);
    
    return 0;
}
