#!/bin/sh

python op.py $1
make clean

case "$1" in
0)
	echo "sh: none"
	make -f Makefile_none
	;;
1)
	echo "sh: mpi"
	make -f Makefile_mpi
	;;
2)
	echo "sh: omp"
	make -f Makefile_omp
	;;
3)
	echo "sh: mpi+omp"
	make -f Makefile
	;;
*)
	echo "sh: Error"
	;;
esac

g++ rarara.cpp -o standard_crc
#./standard_crc $str | xargs mpirun -np 10 -loadbalance -hostfile hostfile ./mycrack
#./standard_crc $2 | xargs ./mycrack
python test1.py $1 $2 $3 $4

