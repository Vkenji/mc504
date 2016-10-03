#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "judge.h"
#include "main.h"

void enter_judge ();
void confirm_judge ();
void leave_judge ();

void* f_jdg (void *v) {

    enter_judge ();
    confirm_judge ();
    leave_judge ();
    
    return NULL;
}

/* juiz pode soh entrar se todos os imigrantes que conseguiram certificado sairam.
 Quando juiz entrar, sinalizar aso imigrantes e espectaodores nao podem mais entrar */
void enter_judge () {
    // imprimir juiz entrando
    
    pthread_mutex_lock (&door);
    
    while (entered > 0 )
        pthread_cond_wait(&all_immigrant_leave, &door);
    
    judge_in = 1;
    pthread_cond_signal (&nojudge);
    
    pthread_mutex_unlock (&door);
    
}

/* apos todos que os imigrantes fizerem o checkin, o juiz pode confimar a emissao 
 do certificado, apos a emissao o juiz deve sinalizar os imigrantes */
void confirm_judge () {
    
    pthread_mutex_lock (&certificate_being_done);
    
        while (checked_in < entered)
            pthread_cond_wait (&all_checked_in, &certificate_being_done);
    
        certificate_done = 1;
        pthread_cond_signal (&certificate_validated);
    
    pthread_mutex_unlock (&certificate_being_done);
}

/* quando o juiz sair, ele deve avisar que saiu */
void leave_judge () {
    pthread_mutex_lock (&door);
    
    judge_in = 0;
    pthread_cond_signal (&nojudge);
    
    pthread_mutex_unlock (&door);
    
    
}


