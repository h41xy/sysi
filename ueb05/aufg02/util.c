#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

 
/* legt den gemeinsamen Speicher an */
int shm_create(size_t size) {
	return shmget(IPC_PRIVATE, size, 0666);
}

/* bindet den Speicher ein */
void* shm_pointer(int shmid) {
	return shmat(shmid, NULL, 0);
}

/* gibt den Speicher frei */
int shm_remove(int shmid) {
	struct shmid_ds sb;

	if (shmctl(shmid, IPC_RMID, &sb) < 0) {
		return -1;
	}

	return 0;
}

/* erzeugt eine neue Gruppe Semaphoren */
int sem_create(int n) {
	return semget(IPC_PRIVATE, n, 0666);
}

/* Setzen des Semaphorwertes */
int sem_set(int semid, int value) {
	return semctl(semid, 0, SETVAL, value);
}

/* dekrementiert den Wert eines Semaphores */
int sem_down(int semid) {
	struct sembuf sb;

	sb.sem_num = 0;
	sb.sem_flg = 0;
	sb.sem_op = -1;

	if (semop(semid, &sb, 1) < 0) {
		return -1;
	}

	return 0;
}

/* inkrementiert den Wert eines Semaphores */
int sem_up(int semid) {
	struct sembuf sb;

	sb.sem_num = 0;
	sb.sem_flg = 0;
	sb.sem_op =  1;

	if (semop(semid, &sb, 1) < 0) {
		return -1;
	}

	return 0;
}

/* löscht eine Gruppe von Semaphoren */
int sem_remove(int semid) {
	if (semctl(semid, 0, IPC_RMID) < 0) {
		return -1;
	}

	return 0;
}

