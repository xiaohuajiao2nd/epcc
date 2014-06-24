#!/bin/python

import subprocess
import string
import sys
import time

import timer


NODES = 14
ROUNDS = 1000
LENGTH = 5


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

def round(parallelized, rstr):

	def gen_cmd():
		cmd = []
		#print "######", parallelized
		if (parallelized & 1) == 1:
			cmd = "mpirun -loadbalance -hostfile hostfile -np".split(' ')
			cmd.append(str(NODES))
		cmd.append("./mycrack")

		#rstr = random_str(length)
		cmd += get_crc_args(rstr)

		#print "[str]:", rstr
		return cmd

	cmd = gen_cmd()
		
	p = subprocess.Popen(cmd, stdin=subprocess.PIPE,\
			 stdout=subprocess.PIPE, 
			stderr=subprocess.PIPE, shell=False)
	output = p.stdout.read()
	p.wait()
	#cal_time(output)

	#print "'%s'" % ' '.join(cmd), "Done"
	return 

def main(argv):
	def read_data(datafile="data.txt"):
		f = open(datafile)
		tmp = f.readlines()
		f.close()
		data = [i.rstrip('\n') for i in tmp]
		return data

	if len(argv) > 1:
		data = []
		if len(argv) > 2:
			data = read_data(argv[2])
		else:
			data = read_data()

		result = []

		f = open("log/" + time.strftime("%H_%M_%S", time.localtime(time.time())) + ".log", "w")
		for i in xrange(ROUNDS):
			with timer.Timer() as t:
				round(int(argv[1]), data[i])
			print "round %d: %s" % (i, t.secs)
			f.write("round %d: %s - %s\n" % (i, data[i], t.secs))
			
			result.append(t.secs)

		print "Average: " , sum(result) / len(result)
		f.write("Average: %s\n" % (sum(result) / len(result)))
		f.close()


if __name__ == "__main__":
	main(sys.argv)
	#gen_rstr_data(ROUNDS, LENGTH)
