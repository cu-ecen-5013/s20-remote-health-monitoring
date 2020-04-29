ifeq ($(CC),)	
	  CC = $(CROSS_COMPILE)gcc
endif 

ifeq ($(CFLAGS),)
	  CFLAGS = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)	
	 LDFLAGS = -pthread -lrt
endif	   

all: subsystem

subsystem:
	cd humidity && $(MAKE)
	cd tmp102 && $(MAKE)
	cd Server && $(MAKE)

clean:	
	(cd humidity; make clean)
	(cd tmp102; make clean)
	(cd Server; make clean)