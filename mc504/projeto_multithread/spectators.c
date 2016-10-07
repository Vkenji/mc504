#include "spectators.h"
#include "main.h"

void* f_spec(void *v);
void enter_spectator(int id);
void spectate(int id);
void leave_spectator(int id);


void* f_spec(void *v){
    int id = *(int*) v;
    
    enter_spectator(id);
    spectate(id);
    leave_spectator(id);
    
    return NULL;
}

void enter_spectator(int id){
    sleep(1);
    futex_wait(&judge_inside, 1);
    atomic_inc (&entered_spec);
    //printf("Spectator %d has entered.\n", id);
}

void spectate(int id){
    sleep(1);
    //printf("Spectator %d is spectating...\n", id);
}

void leave_spectator(int id){
    //printf("Spectator %d has left.\n", id);
}

