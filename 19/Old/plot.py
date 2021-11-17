#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt

x = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
y = [5, 10, 20, 119, 290, 559, 1264, 2531, 4557, 9216]
plt.scatter(x, y)
plt.xlabel("Number Of Pages")
plt.ylabel("Time Per Access (ns)")
plt.show()