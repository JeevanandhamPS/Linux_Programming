				///    SCHOOL OF LINUX    ///

//author 	=> "Jeevanandham.P.S"
//created date	=> 21jan2019


#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#include<string.h>

unsigned char str[] = "Message from process5 reached process6 successfully";

int main()
{
	mqd_t mqopen;
	int mqsnd,cls;

	//open a message queue
	mqopen = mq_open("/queue1",O_RDWR);
	perror("mq_open");

	//send a message to message queue
	mqsnd = mq_send(mqopen,str,strlen(str)+1,996);
	perror("mq_send");

	cls = mq_close(mqopen);
	perror("mq_close");
}
