/***************************************/
/* Author	: Jeevanandham P S     */
/* Date		: 1-mar-2019           */
/* Filename	: basic_info.h         */
/* Description	: header files         */
/***************************************/

#ifndef BASIC_INFO_H
#define BASIC_INFO_H


/* Included header files */

#include <stdio.h>
#include <time.h>
#include <error.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
 
/* Macro Definitions */

#define hour  tme->tm_hour
#define min   tme->tm_min
#define sec   tme->tm_sec
#define date  tme->tm_mday
#define month tme->tm_mon
#define year  tme->tm_year
#define day   tme->tm_wday
#define yday  tme->tm_yday

#define BLACK	"\x1b[30m"
#define RED	"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define PINK	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define WHITE	"\x1b[37m"
#define RESET	"\x1b[0m"
 
/* function prototypes */

void get_username();    /* To get a user name */
void get_time_date();   /* To get a time and date */
void get_ram_size(int); /* To get a RAM size and details */
void get_rom_size(int); /* To get a ROM size and partition details */
void get_os_info(int);  /* To get an information about OS */
void get_cpu_info(int); /* To get an information of CPU */
void get_battery_status(int); /* To get a battery status */
void help();

/* user defined datatype definitions */

#endif //BASIC_INFO_H
