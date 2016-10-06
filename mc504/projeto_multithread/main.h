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
/* protege a porta */
pthread_mutex_t door;

/* sinalisa quando o juiz entrou */
pthread_cond_t judge;
/* judge_in = 1 juiz entrou, caso contrario nao entrou */
volatile int judge_in;
/* numero de imigrantes que fizeram check in */
volatile int entered;

/* caixas disponiveis para realizacao do CheckIn, protege check_in */
pthread_mutex_t attendant;
/* controla quantos imigrantes fizeram o checkin */
volatile int checked_in;
/* quando todos os imigrantes fizerem o checkin, devemos sinalizar para o juiz */
pthread_cond_t all_checked_in;

/* processo de validacao do cerificado */
/* imigrantes soh podem pegar o certificado apos a liberacao do juiz */
/* talvez nao precise dessas variaveis */
pthread_mutex_t certificate_being_done;
pthread_cond_t certificate_validated;
volatile int certificate_done;

/* juiz soh pode entrar se todos os imigrantes que pegaram o certificado sairam */
pthread_cond_t all_immigrant_leave;
