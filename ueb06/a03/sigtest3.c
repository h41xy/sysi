#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

volatile int signo;
char signalstring;

void printUsage(void);
void sig_handler(int);
void segfault_handler(int);
void divzero_handler(int);
void abort_handler(int);
void alarm_handler(int);

int divzero, segfault, sigabort, sigalarm;

int main(int argc, char **argv) {

  divzero = segfault = sigabort = sigalarm = 0;

  if (argc > 2) {
    printUsage();
    exit(0);
  }
  
  if (argc == 2) {
    if ((*argv[1] - '0') == 1)
      divzero = 1;
    else if ((*argv[1] - '0') == 2)
      segfault = 1;
    else if ((*argv[1] - '0') == 3)
      sigabort = 1;
    else if ((*argv[1] - '0') == 4)
      sigalarm = 1;
    else {
      printUsage();
      exit(0);
    }
  }
    
  int count = 1;  
  signo = 0;

  struct sigaction sa;
  sa.sa_handler = sig_handler;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  while (count <= 32) {
    if (count == 8 || count == 11 || count == 14 || count == 17 || count == 19)
      count++;
        if (count == 9)
          count++;

    if (sigaction(count, &sa, NULL) == -1) {
      perror("Sigaction");
      return EXIT_FAILURE;
    }
    count++;
  }

  sa.sa_handler = segfault_handler;
  if (sigaction(SIGSEGV, &sa, NULL) == -1) {
    perror("Sigaction");
    return EXIT_FAILURE;
  }

  sa.sa_handler = divzero_handler;
  if (sigaction(SIGFPE, &sa, NULL) == -1) {
    perror("Sigaction");
    return EXIT_FAILURE;
  }

  sa.sa_handler = abort_handler;
  if (sigaction(SIGABRT, &sa, NULL) == -1) {
    perror("Sigaction");
    return EXIT_FAILURE;
  }

  sa.sa_handler = alarm_handler;
  if (sigaction(SIGALRM, &sa, NULL) == -1) {
    perror("Sigaction");
    return EXIT_FAILURE;
  }

  if (sigabort)
    abort();

  if (segfault)
    printf("%s\n", count);

  int b = 0;
  if (divzero)
    count = count / b;

  if (sigalarm)
    alarm(5);
  
  sleep(60);

  if (signo == 0)
    return EXIT_SUCCESS;
  else
    return signo;
}

void sig_handler(int sig) {
  signo = sig;
}

void divzero_handler(int sig) {
  psignal(sig, &signalstring);
  exit(sig);
}

void segfault_handler(int sig) {
  psignal(sig, &signalstring);
  exit(sig);
}

void abort_handler(int sig) {
  psignal(sig, &signalstring);
  exit(sig);
}

void alarm_handler(int sig) {
  psignal(sig, &signalstring);
  exit(sig);
}

void printUsage() {
    printf("Usage:\nMaximal ein optionales Argument.\n");
    printf(">1< fuer Div by Zero\n");
    printf(">2< fuer Seg Fault\n");
    printf(">3< fuer Abort\n");
    printf(">4< fuer Alarm nach 5s\n");
}
