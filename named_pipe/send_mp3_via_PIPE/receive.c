		/// SCHOOL OF LINUX ///

//Author 	  => "Jeevanandham.P.S"
//Date of created => 21jan2019


// create named pipe and read a data from other end of the pipe and write it on new .mp3 file..


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<error.h>
#include<fcntl.h>

int main()
{
	int mkd,size,fd;
	ssize_t rd_t,rd_1;

	//make a named PIPE 
	//PIPE name is FIFO...

	mkd = mknod("FIFO", 0644 | S_IFIFO,0);
	perror("mknod");

	//open a Pipe with readonlyn permission...
	
	fd = open("FIFO",O_RDONLY);
	perror("open");

	//read a data from other end of the pipe...

	rd_t = read(fd,&size,4); // receiving size..(integer..4 Bytes)
	perror("read");

	unsigned char song_str[size];

	//we got size of the content that much size we can read...

	rd_1 = read(fd,song_str,size);
	perror("read");

	//finally we had the .mp3 codes so we will open new .mp3 and then write the codes on that .mp3 file... 	
	fd = open("./song.mp3", O_CREAT|O_WRONLY,0740);
	perror("open");

	rd_1 = write(fd,song_str,size);
	perror("write");	

	close(fd);
	perror("close");
}
