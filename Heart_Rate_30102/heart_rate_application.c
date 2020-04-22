//https://elinux.org/Interfacing_with_I2C_Devices
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

#define TMP102_Addr	0x57
#define I2C_BUS_FILE "/dev/i2c-1"


int main(void) {

	int file;

	char filename[40];

	int addr = TMP102_Addr; // The I2C address

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

	char address[10] = {0};

	char address_1[10] = {0};

	address[0] = 0x02;

	address_1[0] = 0x06;

	write(file, address, 1);

	//write(file, address, 1);

	sleep(1);

	write(file, address_1, 1);

	int error_count = 0;
	
	while(1) 
	{
		char buf[1] = { 0 };
		int k = read(file, buf, 3);
		if ((k != 2)) 
		{
			error_count++;
			printf("error: %s (%d) %d\n", strerror(errno), errno, error_count);
		} 
		else 
		{

			int temp_val;

			printf("Value of Buffer 0 = %d\n",buf[0]);

			printf("Value of Buffer 1 = %d\n",buf[1]);


			// printf("String Value of Buffer 0 = %s\n",buf[0]);

			// printf("String Value of Buffer 1 = %s\n",buf[1]);



			temp_val = ((buf[0]) << 8) | (buf[1]);
			
			temp_val >>= 4;

			if (temp_val & (1 << 11))
				temp_val |= 0xF800;

			//printf("Curernt temperature value is :  %04f \t and error is :  %d\n", temp_val * 0.0625, error_count);

		}
		sleep(5);//Sleep for 5 seconds

	}
	return 0;
}
