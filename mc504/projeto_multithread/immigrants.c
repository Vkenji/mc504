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
    
    enter_immigrant ();
    checkIn_immigrant ();
    get_certificate_immmigrant ();
    return NULL;
}

/* imigrantes podem entrar se nao existe juiz trabalhando */
void enter_immigrant () {
    pthread_mutex_lock (&door);
    
    // imprimir imigrante entrando
    while (!judge_in)
        pthread_cond_wait (&nojudge, &door);
    
    entered++;
    
    pthread_mutex_unlock (&door);
}

/* imigrantes que entraram devem fazer checkin.
 Quando todos os imigrantes fizeram checkin, sinalizar ao juiz */
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

/* apos o validacao do cerficado, os imigrantes podem pegar o certificado e sair */
void get_certificate_immmigrant () {
    pthread_mutex_lock (&certificate_being_done);
    
        while (!certificate_done)
            pthread_cond_wait(&certificate_validated, &certificate_being_done);
    
        leave_immigrant();
    
    pthread_mutex_unlock (&certificate_being_done);
}

/* quando o juiz sair, os imigrantes podem sair. 
 Quando o ultimo imigrante sair, ele deve avisar que um novo juiz podem entrar.
 SOLUCAO DO PROBLEMA ESTENDIDO */
void leave_immigrant () {
    pthread_mutex_lock (&door);
    
        // imprimir imigrante saindo
        while (judge_in) {
            pthread_cond_wait (&nojudge, &door);
            entered--;
            if (entered == 0)
                pthread_cond_signal (&all_immigrant_leave);
        }
    
    pthread_mutex_unlock (&door);
    
}
