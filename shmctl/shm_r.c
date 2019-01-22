#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int shmid,fd,shm;
	ssize_t red;
	int *data_read,*ptr;
	unsigned char str[100];

	shmid = shmget(10, 4096, 0);
	perror("shmget : ");

	data_read = shmat(shmid,NULL,0);
	perror("shmat : ");

	printf("%d\n",*data_read);

	shmdt(data_read);
	perror("shmdt : ");


	shm = shmctl(shmid,IPC_RMID,NULL);
	perror("shmctl");
}
