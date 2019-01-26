/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 26jan2019            */
/* Filename     : list.c               */
/* Description  : ls command	       */
/*                (main function)      */
/***************************************/

/* Included header files */
#include "list.h"

/* Global variable definitions */



/* function definitions */
int main(int argc, char *argv[])
{

//RID1
	/* While executing create the executable as my_ls*/

	DIR *fd,*fd1; /*DIR datatype represents a data stream*/
	struct file file_nm;/*user define data type, ddefinitions placed in list.h*/
	unsigned char (**name);
	unsigned char *msg;
	int i;
	struct dirent *reddr,*reddr1;/*inode_no. directory_name serial_no. name_of_entry placed in dirent structure*/

//RID2
	/*without user arguments.. list the current directory files*/

	if(argc==1)
	{
		fd = opendir("."); /*open the current directory*/
		perror("opendir");
		ls(fd,&file_nm); /*ls function definitions in ls.c, prototype placed in list.h (gothrough the both files)*/
		name = (unsigned char **)file_nm.f_name;/*ls function write a file names on file_nm.f_name(user defined datatype)*/
		/*list the files present in current directory*/
		for(i=0;i<(file_nm.max);i++,name++)
			printf("%s\n",*name);	
	}

//RID3
	/* Chech the user passed argument as directory or not*/

	/*user passing argument,we need to check whether the argument is directory or not,if it is a  directory list out it */
	else if(argc>1)
	{
		fd1 = opendir(argv[1]); /*open the directory(passed argument)*/
		perror("opendir");

//RID4
	/*Read the content the user passed argument named direoctoy*/		
		/* opendir return otherthen NULL */
		if(fd1!=NULL)
		{
			ls(fd1,&file_nm);/*ls function definitions in ls.c, prototype placed in list.h (gothrough the both files)*/

//RID5
	/*List the directory information in sorting format*/			
			name = (unsigned char **)file_nm.f_name;/*ls function write a file names on file_nm.f_name(user defined datatype)*/
			 /*list the files present in current directory*/
			for(i=0;i<(file_nm.max);i++,name++)
				printf("%s\n",*name);	
		}
		/* if argument is not a directory means check whether the argument as file or something else by using passed argument*/

//RID6
	/* check the passed argument is valuable or not */
		else
		{
			/* Refer the file_name.c */
			msg = file_name(argv[1]); /*pass the argument to the file_name, it check whether the passed argument is available or not*/

//RID7
	/*Display the status about the entered argument*/
	/*if passed argument proper, print the file name */
			printf("%s\n",msg); /*print the return value from the file_name*/
		}
	}
}
