#! /usr/bin/env python3

import subprocess as sp
import matplotlib.pyplot as pl
import numpy as np

URL = "/home/zdravko/Desktop/BSYS/15/relocation.py"
LIMIT_MAX = 1000
ADRESS_SPACE = 500
NUMBER_OF_TRIALS = 1000
RANDOM_SEED = 0


def count_valid(output):
    valid_counter = 0
    for s in output[11:]:
        if s.__contains__("VALID"):
            valid_counter += 1
    return valid_counter


def plot(result):
    pl.xlabel("Limit")
    pl.ylabel("Erfolgsrate")
    pl.plot(range(LIMIT_MAX), result)
    pl.show()


if __name__ == '__main__':
    cmd = "python3 " + str(URL) + " -c -s " + str(RANDOM_SEED) + " -a " + str(ADRESS_SPACE) + " -n " + str(NUMBER_OF_TRIALS) + " -l "
    result = np.zeros(LIMIT_MAX)
    for l in range(LIMIT_MAX):
        cmd2 = cmd + str(l)
        p = sp.Popen(cmd2, shell=True, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.STDOUT, close_fds=True)
        output = p.stdout.read()
        output = output.decode("utf8").split("\n")
        result[l] = count_valid(output) / NUMBER_OF_TRIALS

    plot(result)