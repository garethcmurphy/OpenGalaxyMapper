# $Id: GNUmakefile,v 1.1.1.1 2004/01/13 12:38:52 gmurphy Exp $ 
# C compiler and flags
#export CC = g++
export MPICH_CCC = icpc
export MPICH_CCLINKER = icpc
export CC = g++
INCLUDEDIR = ../include/  
MPIDIR = /opt/homebrew/include/
#GCC C Compiler Flags
#export CFLAGS =-pg  -Wall -I$(INCLUDEDIR)  -I/usr/include/g++-3/
#export LDFLAGS = -lm 
#Intel Compiler Flags
#export CFLAGS = -I$(INCLUDEDIR) -I$(MPIDIR) -Wall -c -O3 -unroll -tpp7 -axW -xW
#export LDFLAGS = -i_dynamic -g -O3 -unroll -tpp7 -axW -xW

#export CFLAGS = -I$(INCLUDEDIR) -I$(MPIDIR) -w -c -g
export CFLAGS = -I$(INCLUDEDIR)  -w -c -g -I$(MPIDIR)
export LDFLAGS = -g -L/opt/homebrew/lib -lmpi 
all:
	$(MAKE) -C src
write_params:
	$(MAKE) -C src write_params
clean:
	$(RM) *~
	$(MAKE) -C src clean
clobber:
	$(RM) *~
	$(MAKE) -C src clobber
tar:
	tar czvf extinction.tar.gz src/ include/ GNUmakefile
