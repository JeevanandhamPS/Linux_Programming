
/***************************************/
/* Author	: Jeevanandham.P.S     */
/* Date		: 23jan2019            */
/* Filename	: shm_send.c           */
/* Description	: posix_shm receive    */
/***************************************/


#include "shmsend.h"

unsigned char str[] = "POSIX shared memory as working sucessfully";

int main()
{
	int shmfd,sync,unmap,size,ulin;
	unsigned char *vir_addr;
	ssize_t wrt;

	size = strlen(str);

	//Create and open a POSIX shared memory..
	shmfd = shm_open("/shared_posix", O_CREAT | O_RDWR, 0644);//shm_open returns a descriptor to shmfd..
	perror("shm_open");

	wrt = write(shmfd,str,size);//write a string..

	//we need an virtual address to share a memory..
	vir_addr = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,shmfd,0);//mmap always return virtual address of the file descriptor(4th argument)..
	perror("mmap");

	//synchronize a file with a memory map..
	sync = msync(vir_addr,size,MS_SYNC);//virtual address as mapped..
	perror("msync");

	//unmapping..
	unmap = munmap(vir_addr,10);
	perror("munmap");
	return 0;
}
