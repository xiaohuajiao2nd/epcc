#!/bin/python

import subprocess
import random
import string
import sys

import timer

dic = string.letters + string.digits

NODES = 14
LENGTH = 4

def random_str(length):
	return ''.join([random.choice(dic) for i in xrange(length)])

def get_crc_args(rstr):
	cmd = ["./standard_crc", rstr]
	p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
	return p.stdout.read().split(' ')
	
def cal_time(output):
	times = {}
	lines = output.split('\n')
	print output
	for i in lines:
		if "Time" in i:
			tmp = i.split(' ')
			id = int(tmp[1])
			time = float(tmp[3])
			times[id] = time
	print times
	
def round(length):
	cmd = "mpirun -loadbalance -hostfile hostfile -np".split(' ')
	cmd.append(str(NODES))
	cmd.append("./mycrack")

	rstr = random_str(length)
	cmd += get_crc_args(rstr)

	print "[str]:", rstr
	
	p = subprocess.Popen(cmd, stdin=subprocess.PIPE,\
			 stdout=subprocess.PIPE, 
			stderr=subprocess.PIPE, shell=False)

	output = p.stdout.read()
	p.wait()
	cal_time(output)
	#print "'%s'" % ' '.join(cmd), "Done"
	return 

def main(argv):
	result = []
	for i in xrange(2):
		with timer.Timer() as t:
			round(LENGTH)
		print "round: %s s" % t.secs
		result.append(t.secs)

	print "Average: " , sum(result) / len(result)


if __name__ == "__main__":
	main(sys.args)
