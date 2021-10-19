#! /usr/bin/env python3

import subprocess as sp
import matplotlib.pyplot as pl
import numpy as np

URL = "python3 /home/zdravko/Desktop/BSYS/09/lottery.py"
MAX_NUMBER_OF_TIME_UNITS = 1000
RANDOM_SEED = 1789


def get_fairness(i):

    cmd = URL + " -l " + str(i) + ":100," + str(i) + ":100 -c + -s " + str(RANDOM_SEED)
    p = sp.Popen(cmd, shell=True, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.STDOUT, close_fds=True)
    output = p.stdout.read()
    output = output.decode("utf8").split("\n")

    p = [0,0]

    #calculate fairness
    output = output[14:]
    for time in range(len(output)):
        if output[time][10:14] == "DONE":
            job_number = int(output[time][8])
            p[job_number] = time
    if p[0] == 0 or p[1] == 0:
        return 0.5
    elif p[0] > p[1]:
        return p[1] / p[0]
    else:
        return p[0] / p[1]

a = np.zeros(MAX_NUMBER_OF_TIME_UNITS)

for i in range(0,MAX_NUMBER_OF_TIME_UNITS):
    a[i] = get_fairness(i)

pl.plot(range(MAX_NUMBER_OF_TIME_UNITS), a)
pl.semilogx(10)
pl.ylim(0,1)
pl.show()