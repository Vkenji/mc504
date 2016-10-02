#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "judge.h"
#include "main.h"

void enter_leave_judge (int in);
void confirm_judge ();
void leave_judge ();

void* f_jdg (void *v) {
    int in;
    
    in  = 1;
    enter_leave_judge (in);
    confirm_judge ();
    
    in = 0;
    enter_leave_judge (in);
    
    return NULL;
}

void enter_leave_judge (int in) {
    // imprimir juiz entrando
    
    pthread_mutex_lock (&door);
    
        judge_in = in;
        pthread_cond_signal (&nojudge);
    
    pthread_mutex_unlock (&door);
    
}

void confirm_judge () {
    
    pthread_mutex_lock (&certificate_being_done);
    
        while (checked_in < entered)
            pthread_cond_wait (&all_checked_in, &certificate_being_done);
    
        certificate_done = 1;
        pthread_cond_signal (&certificate_validated);
    
    pthread_mutex_unlock (&certificate_being_done);
}
