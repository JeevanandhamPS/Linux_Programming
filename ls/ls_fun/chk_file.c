/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 26jan2019            */
/* Filename     : chk_file.c           */
/* Description  : ls command 	       */
/***************************************/

/* Included header files */
#include "list.h"

/* Global variable definitions */


/*function definitions*/
unsigned char *chk_file(unsigned char *dir,unsigned char *f_name)
{
	DIR *opn;
	struct dirent *reddir;
	int checking;
	unsigned char *name;

        /*if opendir NULL means passed argument is not a directory..*/
	opn = opendir(dir);
	perror("opendir");
	
	/* Check the passed argument in the opened directory or not */
	if(opn!=NULL)
	{
		reddir = readdir(opn); /* read the opened directory */
		perror("readdir");
		checking = 0;
		while(reddir != NULL)
		{
			/* compare the file names to the passed argument */
			if(strcmp(reddir->d_name,f_name)==0)
			{
				checking = 1;
				return f_name; /* return the same file name to the file_name()*/
			}
			reddir = readdir(opn);/*read the open directory*/
			perror("readdir");
		}
		if(checking == 0)/* if no one same as passed argument */
		{
			sprintf(name,"ls: cannot access '%s/%s' : No such file or directory\n",dir,f_name);
			return name; /*return the file name to the file_name()*/
			
		}
	}
	/*passed argument is not a directory*/
	else if(opn==NULL)
	{
		sprintf(name,"%s/%s : no such a directory or file",dir,f_name);
		return name; /* return the string to the file_name()*/
	}
}
