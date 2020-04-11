ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt 
endif

all: tmp102

tmp102: tmp102.c
	$(CC) $(CFLAGS) $(INCLUDES) tmp102.c -o tmp102 $(LDFLAGS)
# aesdsocket.o: aesdsocket.c
# 	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c -o aesdsocket.o aesdsocket.c

clean:	
	rm -rf *o tmp102