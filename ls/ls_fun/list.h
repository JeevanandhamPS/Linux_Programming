/***************************************/
/* Author       : Jeevanandham.P.S     */
/* Date         : 24jan2019            */
/* Filename     : list.h               */
/* Description  : header files         */
/***************************************/

#ifndef LIST_H
#define LIST_H

/* Included header files */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

/* Macro Definitions */

/* user defined datatype definitions */
struct file
{
	unsigned char *(*f_name)[];
	int max;
};


/* function prototypes */
void ls(DIR *,struct file *);
unsigned char *file_name(unsigned char *);
unsigned char *chk_file(unsigned char *,unsigned char *);


#endif //LS_H
