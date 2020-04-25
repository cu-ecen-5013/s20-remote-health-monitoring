ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt 
endif

all: humidity
	
humidity: humidity.c
	$(CC) $(CFLAGS) $(INCLUDES) humidity.c -o humidity $(LDFLAGS)
clean:	
	rm -rf *o humidity