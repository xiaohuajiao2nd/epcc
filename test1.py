#!/bin/python

import subprocess
import string
import sys
import time

import timer


NODES = 13
ROUNDS = 100
LENGTH = 7

def get_crc_args(rstr):
	cmd = ["./standard_crc", rstr]
	p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
	return p.stdout.read().split(' ')
	
def round(f, index, parallelized, rstr):

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
		
	#print cmd
	with timer.Timer() as t:
		p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
		output = p.stdout.read()
		p.wait()

	#print "'%s'" % ' '.join(cmd), "Done"

	print "round %d: %s" % (index, t.secs)
	f.write("round %d: %s - %s\n" % (index, rstr, t.secs))
	f.flush()

	return t.secs

def main(argv):
	def read_data(datafile="data.txt"):
		f = open(datafile)
		tmp = f.readlines()
		f.close()
		data = [i.rstrip('\n') for i in tmp]
		return data

	def trans_op(op, length):
		s = str(length) + "_"
		if op == 0:
			s += "none"
		elif op == 1:
			s += "mpi"
		elif op == 2:
			s += "omp"
		elif op == 3:
			s += "omp_mpi"
		else:
			s += ""
		return s + "_"

	if len(argv) > 1:
		data = []
		if len(argv) > 2:
			data = read_data(argv[2])
		else:
			data = read_data()
		
		if len(argv) > 3:
			ROUNDS = int(argv[3])
		if len(argv) > 4:
			LENGTH = int(argv[4])

		result = []

		f = open("log/" + trans_op(int(argv[1]), LENGTH) + time.strftime("%H_%M_%S", time.localtime(time.time())) + ".log", "w")
		for i in xrange(ROUNDS):
			result.append(round(f, i, int(argv[1]), data[i]))

		print "Average: " , sum(result) / len(result)
		f.write("Average: %s\n" % (sum(result) / len(result)))
		f.close()

#python test1.py op inputfile round length

if __name__ == "__main__":
	main(sys.argv)
