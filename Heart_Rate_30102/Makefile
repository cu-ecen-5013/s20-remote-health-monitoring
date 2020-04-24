ifeq ($(CC),)
	  CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	 CFLAGS = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt 
endif

all: HR_application
	
HR_application: HR_application.c
	$(CC) $(CFLAGS) $(INCLUDES) HR_application.c -o HR_application $(LDFLAGS)
clean:	
	rm -rf *o HR_application