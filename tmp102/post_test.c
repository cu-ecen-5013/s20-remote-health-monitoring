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

#define TMP102_Addr	0x48
#define I2C_BUS_FILE "/dev/i2c-1"

int main(int argc, char* argv[]) {

	printf("****************RUNNING POST TEST FOR TMP102 SENSOR*****************\n");
	int file;
	char filename[40];
	int addr = TMP102_Addr; // The I2C address 
	int config_reg_val =0x01;
	int temp_reg_val =0x00;

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
	
	write(file,&config_reg_val,1);

	u_int16_t buf;

	if( read(file, &buf, 2) != 2){
		printf("*******************POST test failed!**************\n");
		return 1;
	}
else if(buf==0xA060)
		{
			printf("*************POST test passed!****************\n");
		}
printf("Config Register (TMP 102) : %x\n", buf);

write(file,&temp_reg_val,1);

char temp_buff[1] = { 0 };
read(file, temp_buff, 2);
int temp_val;
temp_val = ((temp_buff[0]) << 8) | (temp_buff[1]);
temp_val >>= 4;
if (temp_val & (1 << 11))
	temp_val |= 0xF800;
printf("Curernt temperature value is : %04f \t \n",temp_val * 0.0625);
return 0;
}
