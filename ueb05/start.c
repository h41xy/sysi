#include <unistd.h> /* fork() wait() */
#include <errno.h> /* perror() */
#include <stdio.h>
#include <sys/wait.h> /* guess what */
#include <sys/resource.h> /* setpriority() */
#include <sys/time.h> /*setpriority(), braucht linux nicht aber BSD*/

int run(int argc, char **argv){ 
  printf("This is run()\n");
  
  // fork process && ausgabe pid child - check ? function
  // Fork fuehrt ALLEN folgenden code aus, einmal als
  // child process und danach als parent.
  // Deshalb wird nach fork die pid 
  // in einer if - else abgefragt welcher prozess 
  // gerade am arbeiten ist und je nachdem halt 
  // kot ausgefuehrt. Steht im example von man 2 wait
  // aber ich habs erst nach rumspielen gerafft.

  pid_t cpid;

  // pid_t ppid; 
  // ppid = getpid();
  // printf("ParentPID:\t%d\n", ppid);

  cpid = fork();

  if (cpid == 0){ /* Child Kot */
  
    printf("I am the child.\nMyPid is:\t%ld\n", getpid());
    // set low prio - check 

    int which = PRIO_PROCESS;
    id_t pid = cpid;
    int priority = 20;
    int ret;

    int myprio;

    // perror abfangen
    ret = setpriority(which, pid, priority);

    myprio = getpriority(which, cpid);

    printf("Myprio is:\t%d\n", myprio);

    // execvp argv[0]
    // perror
    execvp(argv[1], argv);
    perror("Execvp");
    // 


  } else { /* Parent Kot */

    printf("I am the parent.\nMyPID is:\t%ld\n", getpid());
  }

}

int main(int argc, char **argv){
  printf("This is main()\n");

  // check Argc
  run(argc, argv);
}
