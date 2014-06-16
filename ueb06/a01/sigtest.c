#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

volatile int signo;
void sig_handler();

int main(void) {
  signo = 0;
  if (signal(SIGINT,sig_handler) == SIG_ERR) {
    perror("Signal");
    return(EXIT_FAILURE);
  }
  sleep(3);
  //printf("\n%d\n", SIGINT);
  if (signo == 0)
    return EXIT_SUCCESS;
  else
    return signo;
}

void sig_handler() {
  signo = SIGINT;
  //printf("\nSignalnumber:\t%d\n", signo);
}
