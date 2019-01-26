/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 26jan2019            */
/* Filename     : ls.c                 */
/* Description  : ls command 	       */
/***************************************/

/* Included header files */
#include "list.h"

/* Global variable definitions */


/* function definitions*/
void ls(DIR *fd1,struct file *file_nm)
{		
	struct dirent *reddr1;//inode_no. directory_name serial_no. name_of_entry placed in dirent structure

	unsigned int check = 0,size;
	unsigned char *string[4096];
	int i,j,k;
	unsigned char *ptr;
	/*if opendir in list.c return NULL means user argument is not a directory..*/
	if(fd1!=NULL)
	{
		reddr1 = readdir(fd1); /*read the opened directory*/
		perror("readdir");

		size=0;
		/*reddir return the NULL end of the directory entries*/
		while(reddr1 != NULL)
		{
			/* ls command dindn't show the . and .. directories */
			if(reddr1->d_name[0]!='.')  
			{
				string[size] = reddr1->d_name;
				size++;
			}
			reddr1 = readdir(fd1); //read the directory..
			perror("readdir");
		}	
					
		/* sorting the file names */
		k =size-1;
		for(i=0;i<size-1;i++,k--)
			for(j=0;j<k;j++)
				if(strcmp(string[j],string[j+1])>0)// if first string is alphabetically bigger that second one means swap the strings
				{
					ptr = string[j];
					string[j] = string[j+1];
					string[j+1]=ptr;
				}
		file_nm->f_name = &string; /* store the &string to user defined structure placed on list.h*/
		file_nm->max    = size;/* store the size to user defined structure placed on list.h*/

		closedir(fd1); //close the opened directory..
//		perror("closedir");
	}
}
