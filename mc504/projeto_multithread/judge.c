#include <stdatomic.h>
#include "judge.h"
#include "main.h"

void* f_jdg (void *v);
void enter_judge();
void confirm_judge();
void leave_judge();


void* f_jdg (void *v){
    enter_judge();
    confirm_judge();
    leave_judge();
    
    return NULL;
}

void enter_judge(){
    //sleep(1);
    atomic_exchange(&judge_inside, 1);
    //atomic_exchange(&judge_confirmed, 0);
    printf("Judge entered.\n");
    sleep(2);
}

void confirm_judge(){
    
    pthread_mutex_lock (&attentand);
    
    // Barreira: todos os imigrantes tem que fazer check in
    while (entered_immi != checkin)
        pthread_cond_wait (&all_check_in, &attentand);
    
    pthread_mutex_lock (&attentand);
    
    atomic_exchange(&judge_confirmed, 1);
    printf("Judge has confirmed.\n");
    futex_wake(&judge_confirmed, checkin);
    sleep(2);
    
    pthread_mutex_unlock (&attentand);
}

void leave_judge(){
    pthread_mutex_lock (&door);
    
    /* juiz so pode sair se todos os imigrantes pegaram o cerrificado */
    while (checkin != 0)
        pthread_cond_wait (&judge_can_leave, &door);
    
    pthread_mutex_lock (&door);
    
    judge_inside = 0;
    judge_confirmed = 0;
    printf("Judge has left.\n");
    futex_wake(&judge_inside, entered_immi + entered_spec);
    
    // prepara para proximo loop
    entered_immi = 0;
    
    pthread_mutex_unlock (&door);
}
