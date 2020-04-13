# ifeq ($(CC),)
# 	  CC = $(CROSS_COMPILE)gcc
# endif

# ifeq ($(CFLAGS),)
# 	 CFLAGS = -g -Wall -Werror
# endif

# ifeq ($(LDFLAGS),)
# 	LDFLAGS = -pthread -lrt 
# endif

# all: 
# 	+$(MAKE) -C tmp102 heart_rate_application

# clean:	
# 	rm -rf *o ./tmp102/tmp102
# 	rm -rf *o ./Heart_Rate_30102/heart_rate_application

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
	cd Heart_Rate_30102 && $(MAKE)
	cd tmp102 && $(MAKE)

clean:	
	(cd Heart_Rate_30102; make clean)
	(cd tmp102; make clean)