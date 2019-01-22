						///SCHOOL OF LINUX///

//author 	= "Jeevanandham.P.S"
//created date	= 21jan2019

//first process 

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#include<string.h>

unsigned char str[] = "Message from process1 reached process6 successfully";

int main()
{
	mqd_t mqopen;
	int mqsnd,cls;

	//open a message queue(create a new)and open with readwrite permission..
	mqopen = mq_open("/queue1",O_CREAT | O_RDWR,0644,NULL);
	perror("mq_open");

	//send a message to message queue..
	mqsnd = mq_send(mqopen,str,strlen(str)+1,1000);
	perror("mq_send");

	cls = mq_close(mqopen);
	perror("mq_close");
}
