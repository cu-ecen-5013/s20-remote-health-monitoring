ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt 
endif

all: heart_rate_application

heart_rate_application: heart_rate_application.c
	$(CC) $(CFLAGS) $(INCLUDES) heart_rate_application.c -o heart_rate_application $(LDFLAGS)


clean:	
	rm -rf *o heart_rate_application