// generel waere es schoen alle ausgabe in main zu haben
#include <stdio.h>
#include <stdlib.h> /* EXIT_FAILURE */
#include <errno.h> /* perror() */
#include <unistd.h> /* fork() */
#include <sys/wait.h> /* guess what */
#include <sys/types.h> /* wait() */
#include <sys/resource.h> /* setpriority() */
#include <sys/time.h> /*setpriority(), BSD braucht laut manPage diese lib*/
#include <signal.h> /* psignal*/

void output();
int run(int, char**);

pid_t cpidout;
int exitcode, termsig;
int cprio;
char *progname;

int run(int argc, char **argv){ 
  
  // Fork fuehrt ALLEN folgenden code aus, einmal als
  // child process und danach als parent.
  // Deshalb wird nach fork die pid 
  // in einer if - else abgefragt welcher prozess 
  // gerade am arbeiten ist und je nachdem halt 
  // kot ausgefuehrt. Steht im example von man 2 wait
  // aber ich habs erst nach rumspielen gerafft.

  pid_t cpid;

  cpidout = cpid = fork();
  if(cpid == -1){
    perror("Fork");
    exit(EXIT_FAILURE);
  }
  
  if (cpid == 0){ /* Child Kot - in func auslagern */
  


    if (execvp(*argv, argv) == -1){
      perror("Execvp");
      exit(EXIT_FAILURE);
    }

  } else { /* Parent Kot */

    pid_t child;
    int status;

    // set low prio

    int which = PRIO_PROCESS;
    int priority = 20;

    if (setpriority(which, cpid, priority) == -1){
      perror("Set Priority");
      exit(EXIT_FAILURE);
    }

    printf("Myprio is:\t%d\n\n\n", getpriority(which, cpid) );
    cprio = getpriority(which, cpid);   

    child = wait(&status);
    if (child == -1){
      perror("wait");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
      exitcode = WEXITSTATUS(status);
    } 
    if (WIFSIGNALED(status)) {
      printf("Signal %d\n", WTERMSIG(status));
      psignal(WTERMSIG(status), "");
      exitcode = WEXITSTATUS(status);
    }

  }

}

void output(){
  printf("---------------------------------------------\n");
  printf("Programm:\t%s\n", progname);
  printf("Child PID:\t%d\n", cpidout);
  printf("Exitcode:\t%d\n", exitcode);

  printf("Child Priority:\t%d\n", cprio);
}

int main(int argc, char **argv){

  if (argc < 2){
    printf("Bitte geben Sie ein Programm an welches aufgerufen werden soll.\n");
    exit(EXIT_FAILURE);
  }

  progname = argv[1];

  run(argc, argv+1);
  output();
  exit(EXIT_SUCCESS);
}
