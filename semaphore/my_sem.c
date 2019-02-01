/***************************************/
/* Author	: Jeevanandham.P.S     */
/* Date		: 01feb2019 	       */
/* Filename	: my_sem.c             */
/* Description	: semaphore            */
/***************************************/

/* Included header file */
#include "my_sem.h"

/* Global variable definitions */


/* function definitions */

int main()
{
	int semid,semctl_,shmid,semop_;
	char *shm_addr;

	union semun sem_union1;
	struct sembuf my_sembuf;
	
	/* semaphore creation with MY_SEMKEY as key */
	semid = semget(SEM_KEY, NSEMS, PERMISSION);

	/* error msg */
	perror("semget");

	/* create a shared memory */
	shmid = shmget(SHM_KEY, SHM_SIZE, PERMISSION);

	/* error message */
	perror("shmget");

	/* To get a virtual address */
	shm_addr = shmat(shmid, NULL, 0);

	/* error message */
	perror("shmat");

	/* Assign values tom the "union semun" */
	sem_union1.val = 7;

	/* semaphore control*/
	semctl_ = semctl(semid, 0, SETVAL, sem_union1);

	/* error message */
	perror("semctl");

	/* To set a structure values */

	my_sembuf.sem_num = 0;/* first semaphore in array..*/

	my_sembuf.sem_op = -7;/* 7 operations has been perform */
	
	my_sembuf.sem_flg = SEM_UNDO;/*operation flag*/

	printf("Waiting for semaphore lock\n");
	sleep(5);


	/* update semaphore values */
	semop_ = semop(semid,&my_sembuf,1);
	printf("%d\n",semop_);

	/* error msg */
	perror("semop");

	printf("Semaphore locked");
	sleep(5);

	printf("Entering critical area\n");

	/* writing process to the virtual address */
	strcpy(shm_addr,"semaphore working....");
	sleep(5);

	printf("Exiting the critical area\n");


	/* To set the my_sembuf values */
	my_sembuf.sem_op = 7;

	my_sembuf.sem_flg = 0;

	sleep(5);

	printf("Lock released\n");

	/* update semaphore values  */
	semop_ = semop(semid, &my_sembuf, 1);

	/*error msg*/
	perror("semop");
	sleep(5);

	shmdt(shm_addr);
	perror("shmdt");

	return 0;
}
