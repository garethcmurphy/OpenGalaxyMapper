# $Id: GNUmakefile,v 1.3 2004/01/20 15:41:51 gmurphy Exp $ 
#CC=g++
#CC=icpc
VPATH=../src/:../include/
SOURCEDIR=src/
INCLUDEDIR=../include/
sources := $(wildcard *.cpp)
OBJECTS := $(sources:.cpp=.o)
headers := $(wildcard *.h)
# GCC C Compiler Flags
#CFLAGS =-pg  -Wall -I$(INCLUDEDIR)  -I/usr/include/g++-3/
#LDFLAGS = -lm 
#Intel Compiler Flags
#CFLAGS = -I$(INCLUDEDIR) -Wall -c -O3 -unroll -tpp7 -axW -xW
#LDFLAGS = -i_dynamic -g -O3 -unroll -tpp7 -axW -xW
EXECS= "../bin/a.out"
main: $(OBJECTS) $(headers) 
	$(CC) $(LDFLAGS) -o $(EXECS) $(OBJECTS)
.cpp.o:	
	$(CC) $(CFLAGS) $<
clean:
	rm -rf *.o
clobber:
	rm -rf *.o $(EXECS) ../output/*.out ../output/*.ps ../output/*.list ../input/input.dat
tar:
	tar -cvf euler.tar $(SOURCEDIR)*.c $(INCLUDEDIR)*.h README Makefile run plot init.dat
	gzip euler.tar
write_params:
	$(CC) -c $(CFLAGS) -o write_parameters.o write_parameters.c
	$(CC) -Iinclude -o ../bin/write_parameters write_parameters.o
