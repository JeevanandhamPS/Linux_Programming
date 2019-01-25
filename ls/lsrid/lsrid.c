

/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 24jan2019            */
/* Filename     : lsrid.c              */
/* Description  : ls command 	       */
/***************************************/



#include "lsrid.h"

int main(int argc, char *argv[])
{
  //RD1
	//While compiling, make executable file named as my_ls "gcc file -o my_ls"	

	DIR *fd,*fd1; //DIR datatype represents a data stream
	struct dirent *reddr,*reddr1;//inode_no. directory_name serial_no. na    me_of_entry placed in dirent structure

	int check = 0;
	char str[]=".",str1[]="..";

	//open a directory by using opendir(), On success opendir() return a datastream to type DIR pointer
	fd = opendir("."); // it open a curret directory(".")
	perror("opendir");

	//Check whether user passed an argument or not

  //RD2 
	//if my_ls executing without parameters,list the current directory

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
  //RD3
	//Executing my_ls with one parameter has to check whether the parameter is a directory..
			if(strcmp(reddr->d_name,argv[1])==0)  //comaparing the passed argument with current directory files..
			{
 				
				if(reddr->d_type == DT_DIR)  //check the passed argument is directory or not, DT_DIR point the directory
				{
					check = 1;	     //if passed argument is direcoty means check value is 1..
					printf("Yeah %s is a directory\n",reddr->d_name);
					fd1 = opendir(argv[1]); //open the directory(passed argument)
					perror("opendir");
  //RD4
	//if the passed arugument is directory, read the contents of that directory and list it..

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
