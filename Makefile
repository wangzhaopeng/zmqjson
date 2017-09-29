#CC		= arm-linux-gnueabi-gcc
#CXX		= arm-linux-gnueabi-g++
#LD		= arm-linux-gnueabi-g++ #-lglibc++ ld

CXX		= g++
LD		= g++

INCLUDE		= -I${PWD}/ -I${PWD}/zmq/ -I${PWD}/zmq/inc -I${PWD}/inc -I./

CCFLAG		= -c -std=c++11 $(INCLUDE) #-g -O2 -Wall -Wextra
LDFLAG 		= -lpthread -ldl -lm \
		-L${PWD}/zmq/lib_86 -lzmq \
		#-L${PWD}/zmq/lib_arm -lzmq \
		-L${PWD}/lib



export  CC CXX LD CCFLAG LDFLAG

all:
	-make clean
	-make -C rep
	-make -C req
	-./cp.sh

clean:
	-rm *.o *~
	-make -C rep clean
	-make -C req clean

