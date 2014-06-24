#!/bin/python
#coding: utf-8

import sys

def gen_option(op):
	f = open("options.h", "w")
	f.write("#ifndef _OPTIONS_H_\n#define _OPTIONS_H_\n")

	if (op & 1) != 0:
		f.write("#define HMPI\n")
	if (op & 0x2) != 0:
		f.write("#define HOMP\n")

	f.write("#endif")
	f.close()

if __name__ == "__main__":
	if len(sys.argv) > 1:
		print "op: ", sys.argv[1]
		gen_option(int(sys.argv[1]))

