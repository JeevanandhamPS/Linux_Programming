


/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 24jan2019            */
/* Filename     : ls.c                 */
/* Description  : ls command sample    */
/***************************************/


/* Included header file */
#include "ls.h"

/* Global variable definitions */


/* function definitions*/
int main()
{
	DIR *fd; //DIR datatype represents a data stream
	struct dirent *reddr; //inode_no. directory_name serial_no. name_of_entry placed in dirent structure
	char str[]=".",str1[]="..";
	
	//open a directory by using opendir(), On success opendir() return a datastream to type DIR pointer..	
	fd = opendir("."); // it open a curret directory(".")
	perror("opendir");
	
	//read the entries from the opened directory
	reddr = readdir(fd); // on sucess, readdir() returns a pointer to an object of type struct dirent
	perror("readdir");

	//if readdir returns NULL pointer, That is end of the directory entry
	while(reddr != NULL)
	{
		// ls command dindn't show the . and .. directories
		if(strcmp(reddr->d_name,str)!=0&& strcmp(reddr->d_name,str1)!=0)
			printf("%s\n",reddr->d_name);
		reddr = readdir(fd); // on sucess, readdir() returns a pointer to an object of type struct dirent
		perror("readdir");
	}

	closedir(fd);
	perror("closedir");
	return 0;
}
