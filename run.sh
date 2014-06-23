#!/bin/sh

str=$1
#echo $str
make clean
make
g++ rarara.cpp -o standard_crc
#./standard_crc $str | xargs mpirun -np 10 -loadbalance -hostfile hostfile ./mycrack
./standard_crc $str | xargs ./mycrack
