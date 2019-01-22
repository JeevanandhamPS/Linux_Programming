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
	int shmid,fd,a=10;
	int *data_read;

	shmid = shmget(10, 4096, IPC_CREAT |IPC_EXCL| S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	perror("shmget");

	data_read = shmat(shmid,NULL,0);
	perror("shmat");

	*data_read = a;

	printf("%d\n",*data_read);

	shmdt(data_read);
	perror("shmdt");
}
