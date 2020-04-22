#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <time.h>
int daemon_flag = 0;
#define TMP102_Addr	0x48
#define I2C_BUS_FILE "/dev/i2c-1"

int main(int argc, char* argv[]) {

openlog(NULL, 0, LOG_USER);
	if(argc ==2)                                        
{
   if(strcmp(argv[1],"-d") == 0)
    {
        printf("DAeMoN Mod3!");
        daemon_flag = 1;   
     }                      
}
	int file = 0;
	char filename[40];
	char cmdbuf[256];
	int err = 0;
	int addr = TMP102_Addr; // The I2C address
	time_t gettime;
	struct tm *temp = NULL;
	char *buf2 = NULL;
	sprintf(filename, I2C_BUS_FILE);
	if ((file = open(filename, O_RDWR)) < 0) 
	{
		printf("Failed to Open the Bus");
		printf("error: %s (%d)\n", strerror(errno), errno);
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, addr) < 0) 
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		printf("error: %s (%d)\n", strerror(errno), errno);
		exit(1);
	}
	
	write(file, 0x00, 1);

	sleep(1);

	int error_count = 0;

	while(1) 
	{
	  if(daemon_flag==1)
		{	
			daemon_flag=0;
			
			pid_t pid;

			/* create new process */
			pid = fork ();
			if (pid == -1)
			return -1;
			else if (pid != 0)	
			exit (EXIT_SUCCESS);
	
			/* create new session and process group */
			if (setsid () == -1)
			return -1;
			/* set the working directory to the root directory */
			if (chdir ("/") == -1)
			return -1;
		}

		char buf[1] = { 0 };
		int k = read(file, buf, 2);
		if ((k != 2)) 
		{
			error_count++;
			printf("error: %s (%d) %d\n", strerror(errno), errno, error_count);
		} 
		else 
		{

			int temp_val;

			temp_val = ((buf[0]) << 8) | (buf[1]);
			
			temp_val >>= 4;

			if (temp_val & (1 << 11))
				temp_val |= 0xF800;
	time( &gettime );
	
	temp = localtime( &gettime );
	
	buf2 = asctime(temp);
	
	printf("Time: %s   Current temperature value is :  %04f \t and error is :  %d\n",buf2,temp_val * 0.0625, error_count);

 	snprintf(cmdbuf, sizeof(cmdbuf), "python2.7 /bin/mqtt/publisher.py T:%04fC",temp_val * 0.0625);
 	err = system(cmdbuf);
 	if (err) 
 	{ 
 		fprintf(stderr, "failed to %s\n", cmdbuf); 
         exit(EXIT_FAILURE); 
     }
	//system("python2.7 /bin/mqtt/publisher temp_val");

	syslog(LOG_ERR,"Curernt temperature value is :  %04f \t and error is :  %d\n", temp_val * 0.0625, error_count);
		}
		sleep(5);//Sleep for 5 seconds

	}
	closelog();
	return 0;
}