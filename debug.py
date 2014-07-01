#!/bin/python

import os
import subprocess

f = open("data_4.txt")
data = [i.strip('\n') for i in f.readlines()[:10]]
f.close()

for i in data:
	os.system("./standard_crc " + i + " | xargs ./mycrack")

