#!/bin/sh

rounds=50
for ((len=10;len<=13;len++))
do
	if [ -f "data_${len}.txt" ]; then
		echo "data_${len}.txt exists"
	else
		echo "create data_${len}.txt"
		python gen_data.py $rounds $len
	fi
	for ((op=3;op>0;op--))
	do
		./run.sh $op data_${len}.txt $rounds $len
		#echo $op
	done
done
