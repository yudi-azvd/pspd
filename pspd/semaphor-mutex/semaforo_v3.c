#include <errno.h>              /* errno and error codes */
#include <sys/time.h>           /* for gettimeofday() */
#include <unistd.h>             /* for gettimeofday(), getpid() */
#include <stdio.h>              /* for printf() */
#include <unistd.h>             /* for fork() */
#include <sys/types.h>          /* for wait() */
#include <sys/wait.h>           /* for wait() */
#include <signal.h>             /* for kill(), sigsuspend(), others */
#include <sys/ipc.h>            /* for all IPC function calls */
#include <sys/shm.h>            /* for shmget(), shmat(), shmctl() */
#include <sys/sem.h>            /* for semget(), semop(), semctl() */

#define SEM_KEY		0x1234
#define SHM_KEY		0x4321
#define	NUM_FILHOS	3

int		g_sem_id;
int		g_shm_id;
int		*indice;

struct sembuf	g_lock_sembuf[1];
struct sembuf	g_unlock_sembuf[1];
char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";


void Imprime_texto(void) {
	struct timeval tv;
	int number, tmp_index, i;
		
	/* Este tempo permite que todos os filhos sejam iniciados */
		sleep(1);
	/* Entrando no loop principal */
	while(1) {
		gettimeofday( &tv, NULL );
		number = ((tv.tv_usec / 47) % 3) + 1;
	/* protegendo a memoria compartilhada: entrando na regiao critica */	
		semop( g_sem_id, g_lock_sembuf, 1 );
		tmp_index = *indice;
		for( i = 0; i < number; i++ ) {
			if( ! (tmp_index + i > sizeof(texto_base)) ) {
				fprintf(stderr, "%c", texto_base[tmp_index + i]);
					usleep(1);
			} /* fim-if */
		} /* fim-for */
		*indice = tmp_index + i;
		if( tmp_index + i > sizeof(texto_base) ) {
			fprintf(stderr, "\n");
			*indice = 0;
		} /* fim-if */
		/*  Liberando o semaforo ... */
		semop (g_sem_id, g_unlock_sembuf, 1);
		} /*fim-while */
} /* fim-Imprime_texto */
	
int main() {
  int rtn, count;
  int pid[NUM_FILHOS];
	/* Construindo a estrutura de controle do semaforo */
	g_lock_sembuf[0].sem_num   = 0; g_lock_sembuf[0].sem_op   = -1;g_lock_sembuf[0].sem_flg   = 0;
	g_unlock_sembuf[0].sem_num = 0; g_unlock_sembuf[0].sem_op = 1; g_unlock_sembuf[0].sem_flg = 0;
  /* Criando o semaforo */	
	g_sem_id = semget( SEM_KEY, 1, IPC_CREAT | 0666 );
	semop (g_sem_id, g_unlock_sembuf, 1);

  /* Criando o segmento de memoria compartilhada */
	g_shm_id   = shmget (SHM_KEY, sizeof(int), IPC_CREAT | 0666);
	indice = (int *) shmat(g_shm_id, NULL, 0);
	*indice = 0;
  /* Criando tres filhos */
  rtn = 1;
  for (count = 0; count < NUM_FILHOS; count++ ) {
    if( rtn != 0 ) {
      pid[count] = rtn = fork();
    } else {
      break;
    }
  }

  /* Verificando o valor retornado para determinar se o processo e pai ou filho  */
  if( rtn == 0 ) {
	  /* Estou no processo filho... */
	  printf("Filho %i comecou ...\n", count);
	  Imprime_texto();
  } else {
	  /* Estou no processo pai ... */
	  sleep(15);
	  /* Matando os processos filhos  */
	  kill(pid[0], SIGTERM); kill(pid[1], SIGTERM); kill(pid[2], SIGTERM);
	  /* Removendo a memoria compartilhada e o semaforo */
	  shmctl(g_shm_id, IPC_RMID, NULL);
	  semctl(g_sem_id, 0, IPC_RMID, 0);
  } /* fim-else */
} /* fim-main */
