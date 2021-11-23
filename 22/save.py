#! /usr/bin/env python3

traceFile = open("./trace.txt", "r")

for i in traceFile:
    x = i[3:11]
    x = int(x, 16) >> 12
    print(x)

traceFile.close()