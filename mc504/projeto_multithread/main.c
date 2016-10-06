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
    
    judge_in = 0;
    entered = 0;
    checked_in = 0;
    certificate_done = 0;
    
    pthread_mutex_init (&door, NULL);
    pthread_cond_init (&judge, NULL);
    
    pthread_mutex_init (&attendant, NULL);
    pthread_cond_init (&all_checked_in, NULL);
    
    pthread_mutex_init (&certificate_being_done, NULL);
    pthread_cond_init (&certificate_validated, NULL);
    
    pthread_cond_init (&all_immigrant_leave, NULL);
    
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
    
    pthread_mutex_destroy(&door);
    pthread_cond_destroy(&judge);
    
    pthread_mutex_destroy(&attendant);
    pthread_cond_destroy(&all_checked_in);
    
    pthread_mutex_destroy(&certificate_being_done);
    pthread_cond_destroy(&certificate_validated);
    
    pthread_cond_destroy(&all_immigrant_leave);
    
    return 0;
}
