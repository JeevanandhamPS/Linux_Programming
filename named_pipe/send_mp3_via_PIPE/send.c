				///    SCHOOL OF LINUX    ///

//author 	=> "Jeevanandham.P.S"
//created date	=> 21jan2019

// Read the .mp3 file content and write to read process via FIFO(previously we create named pipe that one..)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <error.h>
#include <fcntl.h>

int main()
{
	int fd,fd_1;
	unsigned int size = 5177693;
	unsigned char song_str[size];
	ssize_t wrt,wrt_1,red_t;

	//open a .mp3 file...
	fd = open("./s.mp3",O_RDONLY);
	perror("open");

	//read a content from .mp3 and store to buffer...
	red_t = read(fd,song_str,size);
	perror("read");

	//OPen the named pipe..
	fd_1 = open("FIFO", O_WRONLY);
	perror("open");
	
	//Write the size of buff to receiving process via named pipe..
	wrt = write(fd_1,&size,4);
	perror("write");

	//Write the buff to receiving process via named pipe..
	wrt_1 = write(fd_1,song_str,size);
	perror("write");

	close(fd);
	close(fd_1);
	perror("close");
}
