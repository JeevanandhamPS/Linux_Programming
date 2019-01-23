		///SCHOOL OF LINUX///
//Author "Jeevanandham.P.S"
//Date   9jan2019

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>

int main()
{
	int mkd,fd;
	unsigned char buff[25];
	ssize_t read_t;
	mkd = mknod("SIGNAL_", 0644 | S_IFIFO, 0);
	perror("mknod");
	
	fd = open("SIGNAL_", O_RDONLY);
	perror("open");
	
	read_t = read(fd,buff,20);
	perror("read");

	printf("%s\n",buff);

	close(fd);
	perror("close");
}
