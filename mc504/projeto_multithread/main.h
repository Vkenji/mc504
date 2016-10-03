#define N_IMG 10
#define N_SPEC 10
#define N_JDG 1
#define N_ATND 10
#define HALL_FULL 10

/* capacidade maxima do hall de entrada */
/* acho que podemos usar o proprio semaforo para controlar
 o numero de immigrantes que entraram */
sem_t hall_cap;

/* controla entrada e saida de imigrantes */
pthread_mutex_t door;
pthread_cond_t nojudge;
int judge_in;
/* numero de imigrantes que fizeram check in */
int entered;

/* caixas disponiveis para realizacao do CheckIn, protege check_in */
pthread_mutex_t attendant;
int checked_in;
pthread_cond_t all_checked_in;

/* processo de valodacao do cerificado */
pthread_mutex_t certificate_being_done;
pthread_cond_t certificate_validated;
int certificate_done;

pthread_cond_t all_immigrant_leave;
