#define _GNU_SOURCE
#include "main.h"
#include "immigrant.h"
#include "spectator.h"
#include "judge.h"
//#include "barrier.h"

int main(){
    pthread_t thr_img[N_IMG], thr_spec[N_SPEC], thr_jdg[N_JDG];
    int i, imgID[N_IMG], specID[N_SPEC];
    
    //sem_init(&all_checked_in, 0);
    judge_inside = 0;
    judge_confirmed = 0;
    
    for(i=0; i<N_IMG; i++){
        imgID[i] = i;
        if(pthread_create(&thr_spec[i], NULL, f_img, (void*) &imgID[i])){
            fprintf(stderr, "Error creating immigrant threads.\n");
            exit(1);
        }
    }
    
    for (i=0; i<N_SPEC; i++){
        specID[i] = i;
        if(pthread_create(&thr_spec[i], NULL, f_spec, (void*) &specID[i])){
            fprintf(stderr, "Error creating spectator threads.\n");
            exit(1);
        }
    }
    
    for (i=0; i<N_JDG+1; i++){
        if(pthread_create(&thr_jdg[i], NULL, f_jdg, NULL)){
            fprintf(stderr, "Error creating judge threads.\n");
            exit(1);
        }
        sleep(6);
    }
    
    // Ta dando segmentation fault nesta regiao, nao sei porque
    /*
     for(i=0; i<N_IMG; i++)
     pthread_join(thr_img[i], NULL);
     
     for(i=0; i<N_SPEC; i++)
    	pthread_join(thr_spec[i], NULL);
     
     for(i=0; i<N_JDG; i++)
    	pthread_join(thr_jdg[i], NULL);
     */
    
    //sem_destroy(&all_checked_in);
    
    return 0;
}


