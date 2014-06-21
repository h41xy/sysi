#include <stdlib.h>
#include <signal.h>
#include <errno.h>

volatile int signo;
void sig_handler(int);

int main(void) {
  int count = 1;
  signo = 0;

  while (count <= 32) {
    // SIGKILL und SIGCONT koennen nicht gehandelt werden
    if (count == 9 || count == 17 || count == 19)
      count++;

    if (signal(count, sig_handler) == SIG_ERR) {
      perror("Signal");
      return(EXIT_FAILURE);
    }
    count++;
  }

  sleep(60);
  if (signo == 0)
    return EXIT_SUCCESS;
  else
    return signo;
}

void sig_handler(int sig) {
  signo = sig;
}
