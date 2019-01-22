				///    SCHOOL OF LINUX    ///

//author 	=> "Jeevanandham.P.S"
//created date	=> 21jan2019


//	In this program we need to receive messages from previous 5 programs, In that five programs we sent a message via single message queue(name:/queue1)...
//	After received messages, we need shared a memory to process7(that one is next program)...

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

unsigned char str1[8192];
unsigned char str2[8192];
unsigned char str3[8192];
unsigned char str4[8192];
unsigned char str5[8192];

unsigned char str[8192];

int main()
{
	mqd_t mqopen;
	int mqsnd,cls;
	ssize_t mq_rcv;
	unsigned int prio;

	
	//we need open the same  message queue "/queue1"    ..note : posix _message queue must be starting with "/"
	mqopen = mq_open("/queue1",O_RDWR);
	perror("mq_open");

	//Receive the all messages by using mq_receive(priority...)

	mq_rcv = mq_receive(mqopen,str1,8192,&prio);
	perror("mq_receive");

	mq_rcv = mq_receive(mqopen,str2,8192,&prio);
	perror("mq_receive");

	mq_rcv = mq_receive(mqopen,str3,8192,&prio);
	perror("mq_receive");

	mq_rcv = mq_receive(mqopen,str4,8192,&prio);
	perror("mq_receive");

	mq_rcv = mq_receive(mqopen,str5,8192,&prio);
	perror("mq_receive");

	int i,j,k=0;

	//5 strings are here so, all of those merge in single string...

	for(j=0;str1[j]!='\0';j++,k++)
		str[k] = str1[j];
	for(j=0;str2[j]!='\0';j++,k++)
		str[k] = str2[j];
	for(j=0;str3[j]!='\0';j++,k++)
		str[k] = str3[j];
	for(j=0;str4[j]!='\0';j++,k++)
		str[k] = str4[j];
	for(j=0;str5[j]!='\0';j++,k++)
		str[k] = str5[j];

	cls = mq_close(mqopen);
	perror("mq_close");
	mq_unlink("/queue1");


	//allocates a system V shared memory segments...
	int shmid,fd;
	char *data_read;

	shmid = shmget(1002, 4096, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //it returns a memory id...
	perror("shmget");

	//matching the shared memory locations...
	data_read = shmat(shmid,NULL,0);
	perror("shmat");

	//In that shared location copying a string...
	strcpy(data_read,str);

	//finally detaching the shm...
	shmdt(data_read);
	perror("shmdt");
}
