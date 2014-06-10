#ifndef __UTIL_H
#define __UTIL_H

#ifndef SEM_A
#define SEM_A 0
#endif

#ifndef SEM_R
#define SEM_R 0
#endif

#define LOGLINE(szMsg) printf("%s\n", szMsg);

int shm_create(size_t size);
void* shm_pointer(int shmid);
int shm_remove(int shmid);

int sem_create(int n);
int sem_set(int semid, int value);
int sem_down(int semid);
int sem_up(int semid);
int sem_remove(int semid);

#endif

