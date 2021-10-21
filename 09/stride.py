#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np


jobs = 2
quantum = 1
jobList = [[0, 100, 0], [1, 100, 0]]
clock = 0
stride = 100

for k in range(200):
    if (jobList[0][2] <= jobList[1][2]):
        (wjob, wrun, wpass) = jobList[0]
    else:
        (wjob, wrun, wpass) = jobList[1]

    # now do the accounting
    if wrun >= quantum:
        wrun -= quantum
    else:
        wrun = 0

    wpass += stride

    # update job list
    jobList[wjob] = (wjob, wrun, wpass)

    clock += quantum

    # job completed!
    if wrun == 0:
        jobs -= 1
        # muss zeitpunkt speichern

    if jobs == 0:
        break

print(jobList)