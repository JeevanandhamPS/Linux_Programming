				/// SCHOOL OF LINUX ///


// Author 	   => "Jeevanandham.P.S"
// Date of created => 21jan2019


//In this program we get a data from the shared memory...


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
	int shmid,fd;
	ssize_t red;
	char *data_read;
	unsigned char str[100];

	//allocates a system V memory segment... with shm_id is 1001...
	shmid = shmget(1001, 4096, 0);
	perror("shmget : ");

	//matching the allocated memory segment...
	data_read = shmat(shmid,NULL,0);
	perror("shmat : ");

	//copy a string from shared memory...
	strcpy(str,data_read);
	perror("strcpy");

	//print the copied string...
	printf("%s\n",str);

	//shared memory as detached...
	shmdt(data_read);
	perror("shmdt : ");
}
