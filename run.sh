#!/bin/sh

rounds=10
log="./log/"

if [ ! -d "$log" ]; then
	echo "mkdir ${log}"
	mkdir $log
fi

for ((len=4;len<=4;len++))
do
	if [ -f "data_${len}.txt" ]; then
		echo "data_${len}.txt exists"
	else
		echo "create data_${len}.txt"
		python gen_data.py $rounds $len
	fi
	for ((op=3;op>=0;op--))
	do
		./exp1.sh $op data_${len}.txt $rounds $len
		#echo $op
	done
done
