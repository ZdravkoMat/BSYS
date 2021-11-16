#!/usr/bin/env python3

import math
import subprocess as sp

#sp.run(["make", "tlb"])

PAGE_SIZE = 1024 * 4
MAX_NUMBER_OF_PAGES_BASE_2 = 12
TRIALS = 1000

import matplotlib.pyplot as pl


def measure(number_of_pages):
    cmd = "./tlb " + str(PAGE_SIZE) + " " + str(number_of_pages) + " " + str(TRIALS)
    p = sp.Popen(cmd, shell=True, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.STDOUT, close_fds=True)
    output = p.stdout.read(1024)

    output = output.decode("utf8").split("\n")

    diff = int(output[0])
    return diff/number_of_pages/TRIALS


if __name__ == '__main__':
    number_of_pages = []
    time = []
    for i in range(1, MAX_NUMBER_OF_PAGES_BASE_2):
        number_of_pages.append(math.pow(2, i))
        number_of_pages.append(math.pow(2, i) * 1.5)

    for n in number_of_pages:
        time.append(measure(n))

    fig, ax = pl.subplots()
    ax.set_xscale('log', basex=2)

    ax.plot(number_of_pages, time, marker='o')
    pl.show()