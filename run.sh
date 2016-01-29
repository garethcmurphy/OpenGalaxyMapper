#!/bin/tcsh
make;
time mpirun ./bin/a.out;
more output/output.dat;
