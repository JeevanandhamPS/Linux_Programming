		///SCHOOL OF LINUX///
//Author "Jeevanandham.P.S"
//Date 	 9jan2019

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<error.h>

void sig(int);

typedef void (*sighandler_t)(int);

int main()
{
	sighandler_t sig_t;
	int mkd,fd;
	unsigned char buff[25] = "Waiting for signal";
	ssize_t write_t;
	

	sig_t = signal(13,sig);
	perror("signal");

	fd = open("SIGNAL_", O_WRONLY);
	perror("open");
	

	write_t = write(fd,buff,20);
	perror("write");

	close(fd);
	perror("close");
}

void sig(int x)
{
	printf("I am SIGPIPE\n");
}
