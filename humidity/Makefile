ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

all: humidity
	
humidity: humidity.c
	$(CC) $(CFLAGS) $(INCLUDES) humidity.c -o humidity -lwiringPi
clean:	
	rm -rf *o humidity