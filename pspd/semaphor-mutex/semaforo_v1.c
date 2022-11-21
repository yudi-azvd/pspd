#include <errno.h>     /* errno and error codes */
#include <signal.h>    /* for kill(), sigsuspend(), others */
#include <stdio.h>     /* for printf() */
#include <sys/ipc.h>   /* for all IPC function calls */
#include <sys/shm.h>   /* for shmget(), shmat(), shmctl() */
#include <sys/time.h>  /* for gettimeofday() */
#include <sys/types.h> /* for wait() */
#include <sys/wait.h>  /* for wait() */
#include <unistd.h>    /* for gettimeofday(), getpid() */
#include <unistd.h>    /* for fork() */

#define SHM_KEY 0x4321
int g_shm_id;
int *indice;

char texto_base[] =
    "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void ImprimeTexto(void) {
  struct timeval tv;
  int number, tmp_index, i;
  int contador = 1;
  while (contador <= 500) {
    gettimeofday(&tv, NULL);
    number = ((tv.tv_usec / 47) % 3) + 1;
    tmp_index = *indice;
    for (i = 0; i < number; i++) {
      if (!(tmp_index + i > sizeof(texto_base))) {
        fprintf(stderr, "%c", texto_base[tmp_index + i]);
        usleep(1);
      }
    }
    *indice = tmp_index + i;
    if (tmp_index + i > sizeof(texto_base)) {
      fprintf(stderr, "\n");
      *indice = 0;
    }
    contador++;
  }
  printf("\n");
}

int main(void) {

  /* Criando o segmento de memoria compartilhada */
  g_shm_id = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);

  /* Vinculando a variavel de indice do vetor na memoria compartilhada */
  indice = (int *)shmat(g_shm_id, NULL, 0);

  /* fazendo essa variavel de indice apontar para o primeiro elemento do vetor
   */
  *indice = 0;

  /* chama a funcao de impressao do alfabeto */
  ImprimeTexto();

  /* libera memoria compartilhada e semaforo */
  // shmctl (g_shm_id, IPC_RMID, NULL);
} /* fim-main */
