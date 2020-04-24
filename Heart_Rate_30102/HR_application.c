#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define I2C_DEVICE "/dev/i2c-1"

#define HR_Addr 0x57

int mode_config[2]={0x09,0x02};
int FIFO_rd_ptr = 0x06;

 __s32 i2c_smbus_access(int file, char read_write, __u8 command, int size, union i2c_smbus_data *data)
 {
     struct i2c_smbus_ioctl_data args;
     
     args.read_write = read_write;
     args.command    = command;
     args.size       = size;
     args.data       = data;

     return ioctl(file,I2C_SMBUS,&args);
 }

 static inline __s32 i2c_smbus_read_word_data(int file, __u8 command)
{
    union i2c_smbus_data data;
    if(i2c_smbus_access(file,I2C_SMBUS_READ,command,I2C_SMBUS_WORD_DATA,&data))
        return -1;
    else
    {
        return 0x0FFFF & data.byte;
    }
}

//https://stackoverflow.com/questions/52975817/setup-i2c-reading-and-writing-in-c-language

int write1(int file, unsigned char device_addr, int command)
{
	uint8_t buffer;
    buffer = command;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg message;
    /*write command to the slave*/
    message.addr  = device_addr;
    message.flags = 0;
    message.len   = sizeof(buffer);
    message.buf = &buffer;

    packets.msgs = &message;
    packets.nmsgs = 1;
    if(ioctl(file,I2C_RDWR,&packets) < 0){
        perror("\n\rError writing single byte");
        return -1;
    }

    return 0;  
}

int write2(int file, unsigned char device_addr, int* command)
{
    uint8_t buffer[2];
    
    buffer[0] = command[0];
    buffer[1] = command[1];
  
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg message;
    /*write command to the slave*/
    message.addr  = device_addr;
    message.flags = 0;
    message.len   = sizeof(buffer);
    message.buf = buffer;


    packets.msgs = &message;
    packets.nmsgs = 1;
    if(ioctl(file,I2C_RDWR,&packets) < 0){
        perror("Error writing a word");
        return -1;
    }

    return 0;    
}


int main(void)
{
    int fd;
    int status;
    uint32_t HR, HR1;

    if((fd = open(I2C_DEVICE,O_RDWR)) < 0){
        perror("Opening I2C file error");
        return -1;
    }

    if(ioctl(fd,I2C_SLAVE,HR_Addr) < 0){
        perror("I2C ioctl error");
        return -1;
    }

    if((status = write2(fd,HR_Addr,mode_config)) != 0) 
    {
        perror("HR Not configured");
        return -1;
    }

    if((status = write1(fd,HR_Addr,FIFO_rd_ptr)) != 0)
    {
        perror("HR read write");
        return -1;
    }

    while(1)
    {

            HR = i2c_smbus_read_word_data(fd,FIFO_rd_ptr);
            printf("\n\r HR Value is: %d",HR);

            for(int i=0; i<32;i++)
            {
            	   HR1 = i2c_smbus_read_word_data(fd,FIFO_rd_ptr++);
            	   printf("\n\r HR Value is from fifo: %d",HR1);
            }
    }
    
    return 0;    
}