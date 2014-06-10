#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "util.h" 

#define N_DATA   10
#define N_SHARED 5

static int mutexid = 0;
static int semfullid = 0;
static int sememptyid = 0;
static int shmid = 0;

int producer() {
	int* buf;
	int* shared;
	int i;
	
	LOGLINE("producer start")

	shared = shm_pointer(shmid);
	if (shared == (void*)-1) {
		perror("shm_pointer");
		return 1;
	}

	buf = (int*)malloc(N_DATA<<2);	
	if (buf == NULL) {
		perror("malloc");
		return 1;	
	}

	srand48(buf[0]);	
	
	for (i=0; i<N_DATA; i++) {
		buf[i] = lrand48();
	}	
	
	for (i=0; i<N_DATA; i++) {
	
		sem_down(sememptyid);          /* Zaehler fuer leere Plaetze dekrementieren */
		sem_down(mutexid);             /* Eintritt in kritischen Abschnitt */

		shared[i%N_SHARED] = buf[i];   /* neues Item in Puffer */
		
		sem_up(mutexid);               /* Verlassen des kritischen Abschnitts */
		sem_up(semfullid);             /* Zaehler fuer volle Plaetze inkrementieren. */

		printf("producer: shared[%d] = %d\n", i%N_SHARED, buf[i]);
	}

	free(buf);	

	LOGLINE("producer end")	
	return 0;
}

int consumer() {
	int* shared;
	int item;
	int i;
	
	LOGLINE("consumer start")

	shared = shm_pointer(shmid);
	if (shared == (void*)-1) {
		perror("shm_pointer");
		return 1;
	}

	for (i=0; i<N_DATA; i++) {
		sem_down(semfullid);          /* Zaehler fuer volle Plaetze dekrementieren */
		sem_down(mutexid);            /* Eintritt in kritischen Abschnitt */
		
		item = shared[i%N_SHARED];    /* Item vom Puffer entnehmen */
		shared[i%N_SHARED] = 0;

		sem_up(mutexid);              /* Verlassen des kritischen Abschnitts */
		sem_up(sememptyid);           /* Zaehler fuer leere Plaetze inkrementieren. */
		
		printf("consumer: shared[%d] = %d\n", i%N_SHARED, item);
	}
	
	LOGLINE("consumer end")
	return 0;
}

int main(int argc, char* argv[]) {
	pid_t pid;	
	int status;
	int ret;	
	
	/* Zaehler fuer volle Plaetze */
	semfullid = sem_create(N_SHARED);
	if (semfullid < 0 || sem_set(semfullid, 0) < 0) {
		ret = 1;
		goto out;
	}
	
	/* Zaehler fuer leere Plaetze */
	sememptyid = sem_create(N_SHARED);
	if (sememptyid < 0 || sem_set(sememptyid, N_SHARED) < 0) {
		ret = 1;
		goto out;
	}

	/* Kritischer Abschnitt */
	mutexid = sem_create(1);
	if (mutexid < 0 || sem_set(mutexid, 1) < 0) {
		ret = 1;
		goto out;
	}

	/* Gemeinsamer Speicher */
	shmid = shm_create(N_SHARED<<2);	
	if (shmid < 0) {
		ret = 1;
		goto out;
	}	

	pid = fork();	/* Kopie des Prozesses erzeugen */

	if (pid > 0) {
		ret = consumer();
		if (waitpid(pid, &status, 0) < 0) {
			perror("waitpid");
		}
	} else if (pid == 0) {
		ret = producer();
		exit(ret);
	} else {
		perror("fork");
		ret = 1;
	}

out:
	sem_remove(semfullid);
	sem_remove(sememptyid);
	sem_remove(mutexid);
	shm_remove(shmid);

	return ret;
}

