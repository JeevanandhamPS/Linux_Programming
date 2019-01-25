/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 24jan2019            */
/* Filename     : lsrid.c              */
/* Description  : ls command 	       */
/***************************************/

/* Included header files */
#include "lsrid.h"

/* Global variable definitions */


/* function definitions */
int main(int argc, char *argv[])
{
  //RID1
	// Name your executable as my_ls
	DIR *fd,*fd1; //DIR datatype represents a data stream
	struct dirent *reddr,*reddr1;//inode_no. directory_name serial_no. na    me_of_entry placed in dirent structure

	int check = 0;
	char str[]=".",str1[]="..";

	//open a directory by using opendir(), On success opendir() return a datastream to type DIR pointer
	fd = opendir("."); // it open a curret directory(".")
	perror("opendir");

	//Check whether user passed an argument or not

  //RID2 
	 //Executing my_ls without parameters has to take the listing directory as current directory.
	//if argument passed, Display the current directory list
 	if(argc==1)
	{
		//read the entries from the opened directory
		reddr = readdir(fd); // on sucess, readdir() returns a pointer to an object of type struct dirent
		perror("readdir");
		
		//if readdir returns NULL pointer, That is end of the directory entry.

		while(reddr != NULL)
		{
			 // ls command dindn't show the . and .. directories
			if(strcmp(reddr->d_name,str)!=0&& strcmp(reddr->d_name,str1)!=0)
				printf("%s\n",reddr->d_name);
			reddr = readdir(fd);// on sucess, readdir() returns a pointer to an object of type struct dirent
			perror("readdir");
			
		}
	}


	else if(argc>1)
	{
		//read the entries from the opened directory
		reddr = readdir(fd); // on sucess, readdir() returns a pointer to an object of type struct dirent
		perror("readdir");
		
		//if readdir returns NULL pointer, That is end of the directory entry.
		while(reddr != NULL)
		{
  //RID3
	//Executing my_ls with one argument has to check wether the passed argument is a directory.
			if(strcmp(reddr->d_name,argv[1])==0)  //comaparing the passed argument with current directory files..
			{
 				
				if(reddr->d_type == DT_DIR)  //check the passed argument is directory or not, DT_DIR point the directory
				{
					check = 1;	     //if passed argument is direcoty means check value is 1..
					printf("Yeah %s is a directory\n",reddr->d_name);
					fd1 = opendir(argv[1]); //open the directory(passed argument)
					perror("opendir");
  //RID4
	//Executing my_ls with one argument has to read the directory contents and display the list of files and directory mentioned in the directory mentioned in the argument.
					reddr1 = readdir(fd1); //read the opened directory
					perror("readdir");
					
					while(reddr1 != NULL)
					{
			 			// ls command dindn't show the . and .. directories
						if(strcmp(reddr1->d_name,str)!=0&& strcmp(reddr1->d_name,str1)!=0)  
							printf("%s\n",reddr1->d_name); //print the file name...
						reddr1 = readdir(fd1); //read the directory..
					}	
					closedir(fd1); //close the opened directory..
					perror("closedir");
				}
			}
			reddr = readdir(fd); //continue the reading of current directory..
			perror("readdir");
		}
		closedir(fd); //close the current directory..
		perror("closedir");

		//Passed argument placed in the current directory 'check = 1', if it is not placed in the current directory 'check = 0'
		if(check==0)
			printf(" %s : no such a directory\n",argv[1]);
	}
}
