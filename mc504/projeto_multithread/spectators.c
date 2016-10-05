#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "spectators.h"
#include "main.h"

void enter_spectators ();
void spectate_spectators ();
void leave_spectators ();

void* f_spec (void *v) {
    int id = *(int*) v;
    
    enter_spectators();
    //spectate_spectators();
    //leave_spectators();

    return NULL;
}

void enter_spectators () {
    pthread_mutex_lock (&door);
    
    // imprimir epectador entrando
    while (!judge_in)
        pthread_cond_wait (&nojudge,&door);
    
    pthread_mutex_unlock (&door);
}
