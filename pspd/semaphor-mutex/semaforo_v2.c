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

#define SHM_KEY		0x4321
#define	NUM_FILHOS	3
int		g_shm_id;
int		*indice;

char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void ImprimeTexto(void) {
	struct timeval tv;
	int number, tmp_index, i;
	
/* Tempo p que todos os filhos sejam iniciados */
	sleep(1);
	while(1) {
		/* Calcula numero randomico atraves auxiliado por uma funcao de tempo */
		gettimeofday( &tv, NULL );
		number = ((tv.tv_usec / 47) % 3) + 1;
		tmp_index = *indice;
		for (i = 0; i < number; i++ ) {
			if( ! (tmp_index + i > sizeof(texto_base)) ) {
				fprintf(stderr, "%c", texto_base[tmp_index + i]);
				usleep(1);
			} /*fim-if */
		} /* fim-for */
		*indice = tmp_index + i;
		if (tmp_index + i > sizeof(texto_base)) {
			fprintf(stderr, "\n");
			*indice = 0;
		} /*fim-if */
	} /* fim-while */
}  /*fim-Imprime_texto */


int main() {
  int rtn, count;
  /* Para armazenar os ids dos processos filhos, permitindo o posterior uso do comando kill */
  int pid[NUM_FILHOS];

/* Criando o segmento de memoria compartilhada */
	g_shm_id   = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);

/* Vinculando a variavel de indice do vetor na memoria compartilhada */	
	indice = (int *) shmat(g_shm_id, NULL, 0);
	
/* fazendo essa variavel de indice apontar para o primeiro elemento do vetor */	
	*indice = 0;

/* Criando tres filhos */
  rtn = 1;
  for( count = 0; count < NUM_FILHOS; count++ ) {
    if( rtn != 0 ) {
      pid[count] = rtn = fork();
    } else {
      break;
    }
  }
/* Verificando o valor retornado para identificar se o processo eh pai ou filho  */
  if (rtn == 0) { 
	  /* Estou no processo filho... */
	  printf("Filho %i comecou ...\n", count);
	  ImprimeTexto();
  } else {
	/* Estou no processo pai ... */
	  sleep(15);
	  /* Matando os processos filhos  */
	  kill(pid[0], SIGTERM); kill(pid[1], SIGTERM); kill(pid[2], SIGTERM);
	  /* Removendo a memoria compartilhada */
	  shmctl (g_shm_id, IPC_RMID, NULL);
  } /* fim-else */
} /* fim-main */
