#!/usr/bin/env python
# encoding: utf-8

import pylab as pl
import os

result = {}
NONE = 0
MPI = 1
OMP = 2
OMP_MPI = 3

def read_average(filename):
    f = open(filename)
    data = float(f.readlines()[-1].split(":")[-1])
    f.close()
    return data

def read_data():
    for filename in os.listdir('.'):
        if filename.endswith(".log"):
            l = int(filename[0])
            if not l in result:
                result[l] = [0.0] * 4
            index = NONE
            if "omp_mpi" in filename:
                index= OMP_MPI
            elif "omp" in filename:
                index = OMP
            elif "mpi" in filename:
                index = MPI

            result[l][index] = read_average(filename)
            #print filename

    #print result
    return result

def paint1(data):
    order_data = sorted(data.items(), key=lambda x: x[0])
    print order_data

    x = [i[0] for i in order_data]

    y0 = [i[1][0] for i in order_data]
    y1 = [i[1][1] for i in order_data]
    y2 = [i[1][2] for i in order_data]
    y3 = [i[1][3] for i in order_data]

    #print "x", x
    #print "y0", y0
    #print "y1", y1


    pl.plot(x, y0, 'r', label="NONE")
    pl.plot(x, y1, 'b', label="MPI")
    pl.plot(x, y2, 'g', label="OMP")
    pl.plot(x, y3, 'y', label="OMP_MPI")

    pl.legend(loc="upper left")
    pl.xticks(list(xrange(3, 11)), [str(i) for i in xrange(3, 11)])
	
    pl.xlabel('String Length')
    pl.ylabel('Time')

    pl.show()


def paint2(data):
    order_data = sorted(data.items(), key=lambda x: x[0])
    print order_data
    dic = ['', "NONE", "MPI", "OMP", "OMP_MPI", '']

    x = [i for i in xrange(4)]
    y0 = order_data[0][1]
    y1 = order_data[1][1]
    y2 = order_data[2][1]
    y3 = order_data[3][1]
    y4 = order_data[4][1]
    #y4 = order_data[4][1]

    #print "x", x
    #print "y0", y0
    #print "y1", y1


    pl.plot(x, y0, 'r', label="length=4")
    pl.plot(x, y1, 'b', label="length=5")
    pl.plot(x, y2, 'g', label="length=6")
    pl.plot(x, y3, 'y', label="length=7")
    pl.plot(x, y4, 'c', label="length=8")
    #pl.plot(x, y4, 'k', label="length=9")

    pl.xticks(list(xrange(-1, 5)), list(dic))

    pl.legend(loc="upper right")
	
    pl.xlabel('Compiling Modes')
    pl.ylabel('Time')
	
    pl.show()


paint1(read_data())
