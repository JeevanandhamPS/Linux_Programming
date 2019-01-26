/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 26jan2019            */
/* Filename     : file_name.c          */
/* Description  : ls command 	       */
/***************************************/

/* Included header files */
#include "list.h"

/* Global variable definitions */


/* function definitions */

unsigned char *file_name(unsigned char *str)
{
	int slash=0,count=0;
	unsigned char *cdr = ".";
	unsigned char *return_name;
	/*Check whether the user passed argument as placed in current directory or other directory*/
	while(str[slash]!='\0')
	{
		if(str[slash] == '/')
			count++;
		slash++;
	}	

	/* The passed argument is not a direcotry means, spread the argument as parent directory and file name, check in parent directory,
	   whether the file is placed or not */
	int i=0,j,length,len,l;
	unsigned char name[256],dir[8192],f_name[256];

	len=length = strlen(str)-1;

	while(str[length] != '/')
	{
		name[i] = str[length];
		length--;
		i++;
	}
	l = strlen(name)-1;
	
	/*arrange the file name and parent directory name*/
	len = len-i;
	for(j=0;j<len;j++)
		dir[j] = str[j];
	for(j=0;l>0;l--,j++)
		f_name[j] = name[l];
	f_name[j] = name[0];

       /* If Passed argument in current directory, pass the current directory address as a parameter in chk_file() */
	
       /* chk_file() palced in list.h */	
       if(count==0)
	       return_name = chk_file(cdr,f_name);	/* Current directory */
       else
	       return_name = chk_file(dir,f_name);	/* other directory */

       return return_name; //return the file name to the main function
}
