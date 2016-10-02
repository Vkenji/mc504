#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "immigrants.h"
#include "main.h"

void enter_immigrant ();
void checkIn_immigrant ();
void sit_down_immgirant ();
void swear_immigrant ();
void get_certificate_immmigrant ();
void leave_immigrant ();

void* f_img (void *v) {
    int id = *(int*) v;
    
    enter_immigrant();
    checkIn_immigrant();

    return NULL;
}

void enter_immigrant () {
    pthread_mutex_lock (&door);
    
    // imprimir imigrante entrando
    while (!judge_in) {
        pthread_cond_wait (&nojudge,&door);
        entered++;
    }
    
    pthread_mutex_unlock (&door);
}

void checkIn_immigrant () {
    
    pthread_mutex_lock (&attendant);
    
        // imprimir que imigrante fazendo check in
        checked_in++;
        sit_down_immgirant();
    
        if (entered == checked_in && judge_in == 1) {
            swear_immigrant();
            pthread_cond_signal (&all_checked_in);
        }
    
    pthread_mutex_unlock (&attendant);
    
}

void sit_down_immigrant () {
    // imprimir imigrante sentado
}
void swear_immigrant () {
    // imprimir imigrante levandando
}

void get_certificate_immigrant () {
    pthread_mutex_lock (&certificate_being_done);
    
        while (!certificate_done)
            pthread_cond_wait(&certificate_validated, &certificate_being_done);
    
        leave_immigrant();
    
    pthread_mutex_unlock (&certificate_being_done);
}

void leave_immigrant () {
    pthread_mutex_lock (&door);
    
        // imprimir imigrante saindo
        while (judge_in) {
            pthread_cond_wait (&nojudge,&door);
            entered--;
        }
    
    pthread_mutex_unlock (&door);
    
}
