#include <stdlib.h>
#include <signal.h>
#include <errno.h>

volatile int signo;
void sig_handler(int);

int main() {
  int count = 1;  
  signo = 0;

  struct sigaction sa;
  sa.sa_handler = sig_handler;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  
  while (count <= 30) {
    if (count == 9 || count == 19)
      count++;

    if (sigaction(count, &sa, NULL) == -1) {
      perror("Sigaction");
      return EXIT_FAILURE;
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
