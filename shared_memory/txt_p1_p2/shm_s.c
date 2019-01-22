			///  SCHOOL OFLINUX   ///



// author	    => "Jeevanandham.P.S"
// date of created  => 21jan2019



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

	//allocate the system V shared memory segment...

	shmid = shmget(1001, 4096, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
	// IRUSR  = user read permission
	// IWUSR  = user write permission
	// IRGRP  = group read permission
	// IROTH  = other read permission 
	perror("shmget");

	//matching the shared the memory segment...
	data_read = shmat(shmid,NULL,0);
	perror("shmat");
	

	// read the content from txt file "It placed on current directory.."...
	fd = open("./txt",O_RDWR);
	perror("open");

	red = read(fd,str,70);
	perror("read");

	//That red content as copy to shared memory location..
	strcpy(data_read,str);
	
	//Detach the location...
	shmdt(data_read);
	perror("shmdt");

	close(fd);
	perror("close");
}
