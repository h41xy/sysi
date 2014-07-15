#include <stdlib.h>
#include <signal.h>

void sig_handler(int);

void main() {
  struct sigaction sa;
  sa.sa_handler = sig_handler;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  
  sigaction(SIGXCPU, &sa, NULL);

  while(1) {}
}

void sig_handler(sig) {
  exit(sig);
}
