
/*###################*\
~   SCHOOL OF LINUX   ~
\*###################*/



/**************************************\
 *				      *	
 *  Author	: Jeevanandham.P.S    *
 *  Date	: 23-01-2019  	      *
 *  Filename	: shm_receive.c	      *
 *  Description	: Explains	      *
 *		  POSIX shared memory *
 *				      *
\**************************************/


#include "pxshm.h"

int main()
{
	int shmfd,sync,unmap,unlin;
	unsigned char *vir_addr;
	unsigned char str[100];

	//Create and open a POSIX shared memory..
	shmfd = shm_open("/shared_posix",O_RDWR, 0644);//shm_open returns a descriptor to shmfd..
	perror("shm_open");

	//we need an virtual address to share a memory..
	vir_addr = mmap(NULL,10,PROT_READ | PROT_WRITE,MAP_SHARED,shmfd,0);//mmap always return virtual address of the file descriptor(4th argument)..
	perror("mmap");

	printf("%s\n",vir_addr);
	
	//synchronize a file with a memory map..
	sync = msync(vir_addr,10,MS_SYNC);//virtual address as mapped..
	perror("msync");

	//unmapping..
	unmap = munmap(vir_addr,10);
	perror("munmap");
	
	//shm_unlink
	unlin = shm_unlink("/shared_posix");
	perror("shm_unlink");

	return 0;
}
