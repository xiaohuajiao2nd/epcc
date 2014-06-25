#!/bin/sh

rounds=100
for ((len=9;len<=10;len++))
do
	if [ -f "data_${len}.txt" ]; then
		echo "data_${len}.txt exists"
	else
		echo "create data_${len}.txt"
		python gen_data.py $rounds $len
	fi
	for ((op=4;op>0;op--))
	do
		./run.sh $op data_${len}.txt $rounds $len
		#echo $op
	done
done
