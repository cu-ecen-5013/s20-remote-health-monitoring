ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

all: server
	
server: server.c
	$(CC) $(CFLAGS) $(INCLUDES) server.c -o server
clean:	
	rm -rf *o server