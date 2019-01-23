		///SCHOOL OF LINUX///

// Author "Jeevanandham.P.S"
// Date	  9jan2019


#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int mkd,fd;
	ssize_t red;
	unsigned char str[30];
	mkd = mknod("My_pipe", S_IFIFO | 0644,0);
	fd   = open("My_pipe", O_RDONLY);
	red = read(fd,str,30);
	printf("%s\n",str);
	close(fd);
}
