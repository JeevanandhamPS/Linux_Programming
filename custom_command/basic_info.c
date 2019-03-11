/***************************************/
/* Author	: Jeevanandham P S     */
/* Date		: 1-mar-2019           */
/* Filename	: basic_info.c         */
/* Description	: basic information    */
/***************************************/

/* Included header file */

#include "basic_info.h"

/* Global variable definitions */


/* function definitions */

int main(int argc, char *argv[])
{
	/*First Check the count of passed argument, if it is less then 2, it's fine */
	/* Otherwise more than 2 means, print the help page to the user */
	if(argc > 2)
		help();

	/* If the passed argument count more than one, check the possiblity of the argument, otherwise print the help page */

	/* options -m -a -o -c -b -h are available, other all are goto the help function */
	if(argc == 2)
	{
		
		if(strcmp(argv[1],"-m")==0 || strcmp(argv[1],"-o")==0 ||strcmp(argv[1],"-c")==0 || strcmp(argv[1],"-b")==0 || strcmp(argv[1],"-a")==0)
		{
			/* To welcome the user, get user name and device name, print the sentence "hai 'user name' this 'device name' "*/
			get_username();
			get_time_date();
		}

		/*If the argument is "-m", Print the information of memory, RAM, ROM details */
		if(strcmp(argv[1],"-m")==0)
		{
			get_ram_size(1);  /* To call the ram checking function */
			get_rom_size(1);  /* To call the ROM checking funtion  */
		}

		/*If the argument is "-o", Print the Operating system details */
		else if(strcmp(argv[1],"-o")==0)
			get_os_info(1);	/* To call the Os_info function */    

		/*If the argument is "-c", Print the Processor details */
		else if(strcmp(argv[1],"-c")==0)
			get_cpu_info(1); /* To call the cpu_info function */      

		/*If the argument is "-b", Print the Battery details */
		else if(strcmp(argv[1],"-b")==0)
			get_battery_status(1); /* To call the battery_status function */    

		/*If the argument is "-a", Print all the above options*/
		else if(strcmp(argv[1],"-a")==0)
		{
			/* To welcome the user, get user name and device name, print the sentence "hai 'user name' this 'device name' "*/
			get_ram_size(1); /* to get basic information of ram */ 
			get_rom_size(1); /* to get basic information of ROM */ 
			get_os_info(1);  /* to get the basic information of OS */  
			get_cpu_info(1); /* to get basic information of processor */     
			get_battery_status(1); /* to get the basic information of battery */   
		}

		else
			help(); /* call the help function */
	}

	/* If the passed argument count one, Print  the possible basic information */

	else if(argc==1)
	{
		/* To welcome the user, get user name and device name, print the sentence "hai 'user name' this 'device name' "*/
		get_username();
		get_time_date();
	
		get_ram_size(0);	/* RAM size function call */
		get_rom_size(0); 	/* ROM size function call */
		get_os_info(0);		/* Operating system info */
		get_cpu_info(0);	/* CPU information */
		get_battery_status(0);	/* battery status */
	}

	return 0;
}


/* To find a user name */
void get_username()
{
	int status;
	struct stat details;
	struct passwd *usr_name;
	struct utsname os_detail;

	/* To get get a Operating system and kernal information by using uname system call */
	int call = uname(&os_detail); /* Information stored in utsname structure variable os_detail */

	/* To get a system status */
	status = stat(".",&details); /* all information stored in details*/

	if(status == -1)
		perror("stat");

	usr_name = getpwuid(details.st_uid); /* To get a user name by using user id */

	/* Print the user name */
	printf("\n \033[01;33mhai %s, This is %s\n\n" RESET,usr_name->pw_name,os_detail.nodename);
}


/* To find the local time and date */
void get_time_date()
{
	time_t tim = time(NULL);
	struct tm *tme;

	unsigned char *day_name[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	unsigned char *month_name[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	/* Get a local time from system */
	tme = localtime(&tim); /* time date and all data stored to tim */

	/* 12:01am to 11:59am print good morning */
	if(hour<12)

		printf("\033[01;33m...GOOD MORNING...\n\n\x1b[0m");
	
	/* 12:00pm to 3pm print good after noon */
	else if(hour >= 12 && hour <=15)
		printf("\033[01;33m...GOOD AFTER NOON...\n\n\x1b[0m");
	
	/* 4:00pm to 7pm print good evening */
	else if(hour >=16 && hour <= 19)
		printf("\033[01;33m...GOOD EVENING...\n\n\x1b[0m");
	
	/*8pm to 11:59pm print good night */
	else if(hour >=20 && hour <=23)
		printf("\033[01;33m...GOOD NIGHT...\n\n\x1b[0m");

	/* convert 24-hour format to 12 hour format, for user convinient */
	if(hour > 12 )
		printf("Time is %d:%d:%dpm IST\n",(hour-12),min,sec);
	
	else
	{
		if(hour==0)
				printf("Time is %d:%d:%dam IST\n",hour+12,min,sec);
	
		else
			printf("Time is %d:%d:%dam IST\n",hour,min,sec);
	}

	printf("Today %s",day_name[day]);
	printf("  Date : %d-%s-%d\n\n",date,month_name[month],year+1900);
}


void get_ram_size(int per)
{

	/* If per==1, Passed argument is "-m", else no argument as passed through on output window */
	struct sysinfo details;
	int info,convert,g;
	float ram_mb,ram_gb,num,size,time;

	/* To get a system information by using sysinfo system call */
	info = sysinfo(&details);

	if(info == -1)
		perror("sysinfo");

	/* We have a size in Byte; convert to GB */
	ram_mb = details.totalram/1024/1024;
	ram_gb = ram_mb/1024;

	convert = (int)ram_gb; /* to make a round value*/
	num  = (ram_gb - convert)*10;	/* separate the values after the decimal point*/
	g = (int)num; /* typecast */
	size = g*0.1;

	/*make it as 2 digits, ex = 1.8G like */
	if(size > 0.5)
		size = (size + 0.1)+ convert;

	time = details.uptime/60;
	time = time/60;

	/* To print the RAM information when user give -m */
	/* This function print the size, free RAM size, Number of current process, time since boot */

	/* Print the details of RAM */
	if(per==1)
	{
		printf(RED "..........  MEMORY INFORMATION  ..........\n\n" RESET);
		printf(CYAN"	         RAM\n\n" RESET);
		printf(GREEN "RAM size			 \t: %gG\n" RESET,size);
		printf("free RAM size			 \t: %ldM\n",details.freeram/1024/1024);
		printf("Shared RAM size			 \t: %ldM\n",details.sharedram/1024/1024);
		printf("Number of current process	 \t: %d processes\n",details.procs);
		printf("Total swap space size		 \t: %ldB\n",details.totalswap);
		printf("free swap space size		 \t: %ldB\n",details.freeswap);
		printf("Seconds since boot		 \t: %ldsec before(%g hour)\n\n",details.uptime,time);
	}
	/* The printed values all are stored in the structure called sysinfo */

	/* passing argument without -m means print the else part */
	/* Print the basic information */
	else
	{
		printf(GREEN "RAM size			 \t: %gG\n" RESET ,size);
	}
}


void get_rom_size(int per)
{
	/* If per==1, Passed argument is "-m", else no argument as passed through on output window */
	unsigned char str[100];
	ssize_t read_t;
        unsigned int fd,size,data;

	/* To open a sda file to read a information */
	fd = open("/sys/block/sda/size",O_RDONLY);
	read_t = read(fd, str, 100); /* read the hard disk size from there, in byte */
	close(fd);
	
	/* convert the size byte to Giga Byte */
	size = atoi(str);
	size = (size/2048);
	size = size/1024;
	
	/* Print the details of ROM */
	if(per==1)
	{
		printf(CYAN "	         ROM\n\n" RESET);
		printf(GREEN "ROM size			 \t: %uG\n\n" RESET,size);
		/* To print the disk partition by using fdisk bash command with system library call */
		data = system("fdisk -l");
		printf(RED "..........................................\n\n" RESET);
	}

	/* passing argument without -m means print the else part */
	/* Print the basic information */
	else
	{
		printf(GREEN "ROM size			 \t: %uG\n" RESET,size);
	}
}


void get_os_info(int per)
{
	/* If per==1, Passed argument is "-o", else no argument as passed through on output window */
	int i,j;
	struct utsname os_detail;

	/* To get get a Operating system and kernal information by using uname system call */
	int call = uname(&os_detail); /* Information stored in utsname structure variable os_detail */

	if(call == -1)
		perror("uname");

	for(i=0;os_detail.version[i]!=' ';i++);

	char os_name[i-5];

	for(i=0,j=4;os_detail.version[j]!=' ';i++,j++)
		os_name[i] = os_detail.version[j];

	/* To print the OS information when user give -o */
	if(per==1)
	{
		printf(PINK "............  OS INFORMATION  ............\n\n" RESET);
		printf("Device Name			 \t: %s\n",os_detail.nodename);
		printf("Kernal 				 \t: %s kernal\n",os_detail.sysname);
		printf("Kernel version			 \t: %s\n",os_detail.release);
		printf("Operating system 		 \t: %s\n",os_name);
		printf("OS details			 \t: %s\n",os_detail.version);
		if(strcmp(os_detail.machine,"x86_64")==0)
			printf("Architecture			 \t: 64bit\n");
		else if(strcmp(os_detail.machine,"x86_32")==0)
			printf("Architecture			 \t: 32bit\n");
		printf(PINK "..........................................\n\n" RESET);
	}
	
	/* passing argument without -o means print the else part */
	/* Print the basic information */
	else
	{
		printf("Device name			 \t: %s\n",os_detail.nodename);
		printf("Kernal 				 \t: %s kernal\n",os_detail.sysname);
		printf("Operating system name and version\t: %s\n\n",os_name);
	}
}


void get_cpu_info(int per)
{
	/* If per==1, Passed argument is "-c", else no argument as passed through on output window */
	int cpu_det;

	/* if per==1, print the details */
	if(per==1)
	{
		printf(GREEN "............  PROCESSOR INFORMATION  ............\n\n" RESET);
		cpu_det = system("lscpu");
		printf(CYAN ".................................................\n\n" RESET);
	}
	
	/* Print the basic details */
	else
	{
		printf("\nProcessor :\n");
		/* To get a CPU information by using system library call */
		cpu_det = system("lscpu | head -n 16 | grep --color=never Model");
		cpu_det = system("lscpu | head -n 16 | grep --color=never Vendor");
		cpu_det = system("lscpu | head -n 12 | grep --color=never Architecture");
		cpu_det = system("lscpu | head -n 5 | grep --color=never CPU");
	}
}


void get_battery_status(int per)
{
	/* If per==1, Passed argument is "-b", else no argument as passed through on output window */
	int bat_info;
	
	/* if per==1, print the details */
	if(per == 1)
	{
		printf(CYAN "..........  BATTERY INFORMATION  ..........\n\n" RESET);
		bat_info = system("upower -d | head -n 36");
		bat_info = system("upower -d | tail -n 25 | grep --color=never time");
		printf(CYAN "............................................\n\n" RESET);
	}

	/* Print the basic details */
	else
	{
		printf("\nBattery :\n");
		bat_info = system(" upower -d | tail -n 25 | grep --color=always  percentage");
		bat_info = system(" upower -d | tail -n 25 | grep  --color=always state ");
		bat_info = system(" upower -d | tail -n 25 | grep  --color=always time");
	}
}


void help()
{
	printf("Usage:\n");
	printf("  basic_info [options]\n");
	printf("Display the basic information about the system\n");
	printf("\nOptions:\n");
	printf(" -a, --all		print all the options output in basic_info like -memory, -os, -battery, -CPU\n");
	printf(" -b, --battery		print the battery details\n");
	printf(" -c, --CPU		print the CPU information\n");
	printf(" -m, --memory		print the details about memory\n");
	printf(" -o, --OS		print the Operating System details\n");
	printf(" -h, --help		display the options\n\n");

	printf("Enter any valid options\n\n");

	exit (0);
}
