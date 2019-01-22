				///    SCHOOL OF LINUX    ///

//author 	=> "Jeevanandham.P.S"
//created date	=> 21jan2019

//get a shared location data from the process6...

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char str1[8192];

int main()
{
	int shmid,fd;
	ssize_t red;
	char *data_read;

	// allocate the same memory segment..."1002"...
	shmid = shmget(1002, 4096, 0);
	perror("shmget");

	// matching the location...
	data_read = shmat(shmid,NULL,0);
	perror("shmat");

	strcpy(str1,data_read);

	//print a final string from process1..5 to process6, process7 print all the data...
	printf("\n%s\n\n",str1);

	shmdt(data_read);
	perror("shmdt");
}
