		///SCHOOL OF LINUX////

//Author "Jeevanandham.P.S"
//Date	 9jan2019


#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

unsigned char str[] = "hii i am FIFO";

int main()
{
	int fd;
	ssize_t wrte;
	fd   = open("My_pipe", O_WRONLY);
	wrte = write(fd,str,strlen(str));
	close(fd);
}
