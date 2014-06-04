// sortier den kram noch ordentlich !
// generel waere es schoen alle ausgabe in main zu haben
#include <unistd.h> /* fork() */
#include <errno.h> /* perror() */
#include <stdio.h>
#include <sys/wait.h> /* guess what */
#include <sys/types.h> /* wait() */
#include <sys/resource.h> /* setpriority() */
#include <sys/time.h> /*setpriority(), braucht linux nicht aber BSD*/
#include <signal.h> /* psignal*/
#include <stdlib.h> /* EXIT_FAILURE */

int run(int argc, char **argv){ 
  
  // Fork fuehrt ALLEN folgenden code aus, einmal als
  // child process und danach als parent.
  // Deshalb wird nach fork die pid 
  // in einer if - else abgefragt welcher prozess 
  // gerade am arbeiten ist und je nachdem halt 
  // kot ausgefuehrt. Steht im example von man 2 wait
  // aber ich habs erst nach rumspielen gerafft.

  pid_t cpid;

  cpid = fork();
  if(cpid == -1){
    perror("Fork");
    exit(EXIT_FAILURE);
  }
  
  if (cpid == 0){ /* Child Kot - in func auslagern */
  
    // set low prio

    int which = PRIO_PROCESS;
    id_t pid = cpid;
    int priority = 20;

    if (setpriority(which, pid, priority) == -1){
      perror("Set Priority");
      exit(EXIT_FAILURE);
    }

    printf("Myprio is:\t%d\n\n\n", getpriority(which, cpid) );

    //while (*argv != '\0'){
    //  printf("%s\n", *argv);
    //  argv+=1;
    //}
    if (execvp(*argv, argv) == -1){
      perror("Execvp");
      exit(EXIT_FAILURE);
    }

  } else { /* Parent Kot */

    pid_t child;
    int status;
    
    child = wait(&status);
    if (child == -1){
      perror("wait");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
      printf("\n\nExit %s, CODE=%d\n", argv[1], WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("Signal %d\n", WTERMSIG(status));
      psignal(WTERMSIG(status), "");
    }

  }

}

int main(int argc, char **argv){

  if (argc < 2){
    printf("Bitte geben Sie ein Programm an welches aufgerufen werden soll.\n");
    exit(EXIT_FAILURE);
  }
  run(argc, argv+1);
}
