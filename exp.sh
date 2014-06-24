#!/bin/sh

rounds=100
for ((len=4;len<=8;len++))
do
	if [ -f "data_${len}.txt" ]; then
		echo "data_${len}.txt exists"
	else
		echo "create data_${len}.txt"
		python gen_data.py $rounds $len
	fi
	for ((op=0;op<4;op++))
	do
		#./run.sh $op data_${len}.txt $rounds $len
		echo $op
	done
done
