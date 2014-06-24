#!/bin/python
#coding: utf-8

import random
import string
import sys

import test1

dic = string.letters + string.digits

def random_str(length):
	return ''.join([random.choice(dic) for i in xrange(length)])

def gen_rstr_data(num, length):
	f = open("data_" + str(length) + ".txt", "w")
	for i in xrange(num):
		f.write(random_str(length) + '\n')
	f.close()

if __name__ == "__main__":
	length = test1.LENGTH
	rounds = test1.ROUNDS

	if len(sys.argv) > 1:
		rounds = int(sys.argv[1])
	if len(sys.argv) > 2:
		length = int(sys.argv[2])

	gen_rstr_data(rounds, length)
